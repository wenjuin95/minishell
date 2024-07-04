/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:53:41 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/15 17:25:39 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RDP_H
# define RDP_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "operations.h"

typedef enum e_ttype
{
	TOK_NUM,
	TOK_PLUS,
	TOK_MINUS,
	TOK_STAR,
	TOK_SLASH,
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_POWER,
	TOK_EOF,
	TOK_ERR,
}	t_ttype;

typedef struct s_token
{
	t_ttype	type;
	int		value;
}	t_token;

typedef struct s_lexer
{
	const char	*start;
	const char	*curr;
}	t_lexer;

typedef struct s_parser
{
	t_lexer	lexer;
	t_token	next_token;
}	t_parser;

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
			t_ops				operator;
			struct s_ast_node	*left;
			struct s_ast_node	*right;
		}	op;
	};
}	t_ast_node;

void	error_msg(const char *msg);
void	init_lexer(t_lexer *lexer, const char *input);
t_token	next_token(t_lexer *lexer);
void	init_parser(t_parser *parser, const char *input);
void	adv_parser(t_parser *parser);

void	parser(const char *input);

int		do_operation(int x, int y, t_ops op);
void	free_tree(t_ast_node *node);
int		eval_ast(t_ast_node *node);
void	print_tree(t_ast_node *node, int depth);
void	handle_parenthesis(t_parser *parser, t_ast_node **node,
			t_ast_node*(*p)(t_parser *));
void	parse_into_ast(const char *input);

#endif