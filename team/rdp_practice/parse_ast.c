/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:22:47 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/13 22:00:05 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

typedef enum s_node_type
{
	NODE_NUM,
	NODE_OP,
	NODE_ERR
}	t_node_type;

typedef struct s_ast_node
{
	t_node_type			type;
	union
	{
		int	value;
		struct s_op
		{
			char				operator;
			struct s_ast_node	*left;
			struct s_ast_node	*right;
		}	op;
	};
}	t_ast_node;

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
		node->op.operator = '-';
		node->op.left = NULL;
		adv_parser(parser);
		node->op.right = parse_base(parser);
	}
	else
	{
		node->type = NODE_ERR;
	}	
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
		temp->op.operator = '^';
		temp->op.left = left;
		adv_parser(parser);
		temp->op.right = parse_factor(parser);
		left = temp;
	}
	return (left);
}

void	print_tree(t_ast_node *node, int depth)
{
	int	i;

	if (node == NULL)
		return ;
	i = 0;
	while (i++ < depth)
		printf("  ");
	if (node->type == NODE_NUM)
		printf("%d\n", node->value);
	else if (node->type == NODE_OP)
	{
		printf("%c\n", node->op.operator);
		print_tree(node->op.left, depth + 1);
		print_tree(node->op.right, depth + 1);
	}
	else
		error_msg("Error node.");
}

void	parse_into_ast(const char *input)
{
	t_parser	parser;
	t_ast_node	*syntax_tree;

	init_parser(&parser, input);
	syntax_tree = parse_factor(&(parser));
	print_tree(syntax_tree, 0);
}
