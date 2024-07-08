/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:44:00 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/08 15:29:52 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_parser //parser: scanner and next token
{
	t_scanner	scanner;
	t_token		next_token; //next token
}	t_parser;

typedef enum e_cmd_type //type of the command
{
	CMD_EXEC,  //command to execute
	CMD_REDIR, //command with redirection
	CMD_PIPE,  //command with pipe
}	t_cmd_type;

// a "base class" for command types
typedef struct s_cmd //syntax tree node: command node in the syntax tree
{
	t_cmd_type	type;  //type of the command
}	t_cmd;

/*************************************************************************************/
// "child classes" from t_cmd
typedef struct s_pipe_cmd //command with pipe
{
	t_cmd_type	type;       //type of the command
	t_cmd		*left_cmd;  //left command
	t_cmd		*right_cmd; //right command
}	t_pipe_cmd;

typedef struct s_redir_cmd //command with redirection
{
	t_cmd_type	type;        //type of the command
	t_list		*redir_list; //list of redirections
	t_cmd		*next_cmd;   //next command
}	t_redir_cmd;

typedef struct s_exec_cmd  //command to execute
{
	t_cmd_type	type;       //type of the command
	char		**argv;     //arguments
	t_list		*redir_list;//list of redirections
}	t_exec_cmd;
/*************************************************************************************/

// Dynamic array for storing argv
typedef struct s_dym_arr //dynamic array: array of strings
{
	int		size;     //number of strings
	int		capacity; //capacity of the array
	char	**arr;    //array of strings
}	t_dym_arr;

typedef struct s_redir_data //redirection data
{
	t_tok_type	type;     //type of token
	char		*value;   //value of token
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