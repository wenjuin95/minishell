/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:44:00 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/03 14:27:29 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_parser
{
	t_scanner	scanner; //scanner
	t_token		next_token; //next token
}	t_parser;

typedef enum e_cmd_type //type of command
{
	CMD_EXEC, //execute command
	CMD_REDIR, //redirect command
	CMD_PIPE, //pipe command
}	t_cmd_type;

// a "base class" for command types
typedef struct s_cmd
{
	t_cmd_type	type; //type of command
}	t_cmd; 

// "child classes" from t_cmd
typedef struct s_pipe_cmd //pipe command
{
	t_cmd_type	type; //type of command
	t_cmd		*left_cmd; //left command
	t_cmd		*right_cmd; //right command
}	t_pipe_cmd;

// typedef struct s_redir_cmd //redirect command
// {
// 	t_cmd_type	type; //type of command
// 	t_list		*redir_list; //list of redirections
// 	t_cmd		*next_cmd; //next command
// }	t_redir_cmd;

typedef struct s_redir_cmd
{
	t_cmd_type	type; //get command type
	char		*filename; //get filename
	mode_t		mode_flag; //get mode flag
	int			fd; //get file descriptor
	t_cmd		*next_cmd; //get next command
}	t_redir_cmd;

typedef struct s_exec_cmd //execute command
{
	t_cmd_type	type; //type of command
	char		**argv; //command
}	t_exec_cmd;

// Dynamic array for storing argv
typedef struct s_dym_arr //dynamic array
{
	int		size; //size of array
	int		capacity; //capacity of array
	char	**arr; //array
}	t_dym_arr;

typedef struct s_redir_data
{
	t_ttype	type; //type of redirection either "<" or ">" or ">>" or "<<"
	char		*value; //value of redirection
}	t_redir_data;

void	parse(const char *line);
void	print_token(t_token token);

#endif