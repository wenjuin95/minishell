/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:59:53 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/27 15:27:23 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H


typedef enum e_cmd_type
{
	CMD_EXEC, //execute command
	CMD_REDIR, //redirect command
	CMD_PIPE, //pipe command
}	t_cmd_type;

typedef struct s_cmd
{
	t_cmd_type	type; //command type
}	t_cmd;

typedef struct s_redir_cmd
{
	t_cmd_type	type; //get command type
	char		*filename; //get filename
	mode_t		mode_flag; //get mode flag
	int			fd; //get file descriptor
	t_cmd		*next_cmd; //get next command
}	t_redir_cmd;

typedef struct s_exec_cmd
{
	t_cmd_type	type; //get command type
	char		**argv; //get argument
}	t_exec_cmd;

typedef void	(*t_command)(t_cmd *);

void	eval_tree(t_cmd	*cmd);
void	command_execute(t_cmd *command);
void	ft_execvp(const char *file, char *const argv[], char **envp);

#endif
