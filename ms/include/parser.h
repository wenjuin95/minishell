/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:44:00 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/10/18 13:38:42 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_parser
{
	t_scanner	scanner;
	t_token		next_token;
	int			status;
}	t_parser;

typedef enum e_cmd_type
{
	CMD_EXEC,
	CMD_REDIR,
	CMD_PIPE,
	CMD_LIST,
	CMD_SUBS,
}	t_cmd_type;

// "base class" for command types
typedef struct s_cmd
{
	t_cmd_type	type;
}	t_cmd;

// "child classes" from t_cmd
typedef struct s_sub_cmd
{
	t_cmd_type	type;
	t_cmd		*child;
}	t_sub_cmd;

typedef struct s_list_cmd
{
	t_cmd_type	type;
	t_tok_type	and_or;
	t_cmd		*left_cmd;
	t_cmd		*right_cmd;
}	t_list_cmd;

typedef struct s_pipe_cmd
{
	t_cmd_type	type;
	t_cmd		*left_cmd;
	t_cmd		*right_cmd;
}	t_pipe_cmd;

typedef struct s_exec_cmd
{
	t_cmd_type	type;
	t_list		*argv_list;
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

t_cmd		*parse(const char *line, t_minishell *m_shell);

// "Constructors" for different syntax tree nodes

t_cmd		*exec_cmd(t_list *argv, t_list *redir);
t_cmd		*pipe_cmd(t_cmd *left, t_cmd *right);


void		add_to_redir_list(t_list **redir_list, t_parser *parser);
void		add_to_argv_list(t_list **argv_list, t_parser *parser);

void		init_parser(t_parser *parser, const char *line);
void		advance_psr(t_parser *parser);
bool		tok_is_redirection(t_tok_type type);
t_cmd		*parse_cmd_list(t_parser *parser, t_minishell *m_shell);
t_cmd		*parse_command(t_parser *parser, t_minishell *m_shell);
void		free_tree(t_cmd *node);
void		syntax_error(t_parser parser);


#endif
