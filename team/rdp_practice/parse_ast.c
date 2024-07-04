/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:22:47 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/15 17:22:43 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

static t_ast_node	*parse_expression(t_parser *parser);

static t_ast_node	*parse_base(t_parser *parser)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (parser->next_token.type == TOK_NUM)
	{
		node->type = NODE_NUM;
		node->value = parser->next_token.value;
		adv_parser(parser);
	}
	else if (parser->next_token.type == TOK_MINUS)
	{
		node->type = NODE_OP;
		node->op.operator = OP_MINUS;
		node->op.left = NULL;
		adv_parser(parser);
		node->op.right = parse_base(parser);
	}
	else if (parser->next_token.type == TOK_LPAREN)
	{
		handle_parenthesis(parser, &node, &parse_expression);
	}
	else
		error_msg("Syntax error.");
	return (node);
}

static t_ast_node	*parse_factor(t_parser *parser)
{
	t_ast_node	*left;
	t_ast_node	*temp;

	left = parse_base(parser);
	while (parser->next_token.type == TOK_POWER)
	{
		temp = malloc(sizeof (t_ast_node));
		temp->type = NODE_OP;
		temp->op.operator = OP_POW;
		temp->op.left = left;
		adv_parser(parser);
		temp->op.right = parse_factor(parser);
		left = temp;
	}
	return (left);
}

static t_ast_node	*parse_term(t_parser *parser)
{
	t_ast_node	*left;
	t_ast_node	*temp;

	left = parse_factor(parser);
	while (parser->next_token.type == TOK_STAR
		|| parser->next_token.type == TOK_SLASH)
	{
		temp = malloc(sizeof(t_ast_node));
		temp->type = NODE_OP;
		if (parser->next_token.type == TOK_STAR)
			temp->op.operator = OP_MULT;
		else
			temp->op.operator = OP_DIV;
		temp->op.left = left;
		adv_parser(parser);
		temp->op.right = parse_factor(parser);
		left = temp;
	}
	return (left);
}

static t_ast_node	*parse_expression(t_parser *parser)
{
	t_ast_node	*left;
	t_ast_node	*temp;

	left = parse_term(parser);
	while (parser->next_token.type == TOK_PLUS
		|| parser->next_token.type == TOK_MINUS)
	{
		temp = malloc(sizeof(t_ast_node));
		temp->type = NODE_OP;
		if (parser->next_token.type == TOK_PLUS)
			temp->op.operator = OP_PLUS;
		else
			temp->op.operator = OP_MINUS;
		temp->op.left = left;
		adv_parser(parser);
		temp->op.right = parse_term(parser);
		left = temp;
	}
	return (left);
}

void	parse_into_ast(const char *input)
{
	t_parser	parser;
	t_ast_node	*syntax_tree;

	init_parser(&parser, input);
	syntax_tree = parse_expression(&parser);
	if (parser.next_token.type != TOK_EOF)
		error_msg("Syntax Error.");
	print_tree(syntax_tree, 0);
	printf("Result: %d\n", eval_ast(syntax_tree));
	free_tree(syntax_tree);
}
