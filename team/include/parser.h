/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:44:00 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/26 11:26:07 by welow            ###   ########.fr       */
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

typedef struct s_cmd
{
	t_cmd_type	type;
}	t_cmd;

typedef struct s_redir_cmd
{
	t_cmd_type	type;
	char		*filename;
	mode_t		mode_flag;
	int			fd;
	t_cmd		*next_cmd;
}	t_redir_cmd;

typedef struct s_exec_cmd
{
	t_cmd_type	type;
	char		**argv;
}	t_exec_cmd;

void	parse(const char *line);
void	print_token(t_token token);
void	init_parser(t_parser *parser, const char *line);
void	advance_psr(t_parser *parser);
void	free_tree(t_cmd *node);

#endif