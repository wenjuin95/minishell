/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:03:17 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/15 17:25:15 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

int	do_operation(int x, int y, t_ops op)
{
	const t_operation	operations[] = {
	[OP_PLUS] = plus, [OP_MINUS] = minus, [OP_MULT] = multiply,
	[OP_DIV] = divide, [OP_POW] = power
	};

	return (operations[op](x, y));
}

void	free_tree(t_ast_node *node)
{
	if (node == NULL)
		return ;
	else if (node->type == NODE_OP)
	{
		free_tree(node->op.left);
		free_tree(node->op.right);
	}
	free(node);
}

int	eval_ast(t_ast_node *node)
{
	int	left_val;
	int	right_val;

	if (node == NULL)
		return (0);
	if (node->type == NODE_NUM)
		return (node->value);
	else
	{
		left_val = eval_ast(node->op.left);
		right_val = eval_ast(node->op.right);
		return (do_operation(left_val, right_val, node->op.operator));
	}
}

void	print_tree(t_ast_node *node, int depth)
{
	int			i;
	const char	operator_char[] = "+-*/^";

	if (node == NULL)
		return ;
	i = 0;
	while (i++ < depth)
		printf("   ");
	if (node->type == NODE_NUM)
		printf("%d\n", node->value);
	else if (node->type == NODE_OP)
	{
		printf("%c\n", operator_char[node->op.operator]);
		print_tree(node->op.left, depth + 1);
		print_tree(node->op.right, depth + 1);
	}
	else
		error_msg("Error node.");
}

void	handle_parenthesis(t_parser *parser, t_ast_node **node,
	t_ast_node*(*p)(t_parser *))
{
	free(*node);
	adv_parser(parser);
	*node = (t_ast_node *)p(parser);
	if (parser->next_token.type != TOK_RPAREN)
		error_msg("Error! Unclosed '('");
	adv_parser(parser);
}
