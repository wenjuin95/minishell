/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:44:00 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/03 21:42:16 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_parser
{
	t_scanner	scanner;
	t_token		next_token;
}	t_parser;

typedef enum e_cmd_type
{
	CMD_EXEC,
	CMD_REDIR,
	CMD_PIPE,
}	t_cmd_type;

// a "base class" for command types
typedef struct s_cmd
{
	t_cmd_type	type;
}	t_cmd;

// "child classes" from t_cmd
typedef struct s_pipe_cmd
{
	t_cmd_type	type;
	t_cmd		*left_cmd;
	t_cmd		*right_cmd;
}	t_pipe_cmd;

typedef struct s_redir_cmd
{
	t_cmd_type	type;
	t_list		*redir_list;
	t_cmd		*next_cmd;
}	t_redir_cmd;

typedef struct s_exec_cmd
{
	t_cmd_type	type;
	char		**argv;
	t_list		*redir_list;
}	t_exec_cmd;

// Dynamic array for storing argv
typedef struct s_dym_arr
{
	int		size;
	int		capacity;
	char	**arr;
}	t_dym_arr;

typedef struct s_redir_data
{
	t_tok_type	type;
	char		*value;
}	t_redir_data;

// "Constructors" for different syntax tree nodes
t_cmd	*exec_cmd(void);
t_cmd	*redir_cmd(t_list *redir_lst, t_cmd *next);
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right);

void	parse(const char *line);
void	print_token(t_token token);
void	init_parser(t_parser *parser, const char *line);
void	advance_psr(t_parser *parser);
void	free_tree(t_cmd *node);

#endif