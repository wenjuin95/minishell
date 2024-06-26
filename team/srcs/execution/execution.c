/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:26:24 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/26 16:03:38 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern char	**environ;

void	eval_tree(t_cmd	*cmd);

void	command_execute(t_cmd *command)
{
	t_exec_cmd	*ecmd;
	pid_t		pid;

	ecmd = (t_exec_cmd *)command;
	// execve(ecmd->argv[0], ecmd->argv, environ);
	// perror("execve");
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		execve(ecmd->argv[0], ecmd->argv, environ);
		perror("execve");
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

void	command_redirection(t_cmd *command)
{
	t_redir_cmd		*rcmd;
	const mode_t	permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	rcmd = (t_redir_cmd *)command;
	// close(rcmd->fd);
	if (open(rcmd->filename, rcmd->mode_flag, permissions) < 0)
		perror("open");
	eval_tree(rcmd->next_cmd);
}

/*
contains an lookup table(array) of functions
to execute when eval_tree() is called for a syntax tree node
*/
void	eval_tree(t_cmd	*cmd)
{
	const t_command	commands[] = {
	[CMD_EXEC] = command_execute,
	[CMD_REDIR] = command_redirection
	};

	commands[cmd->type](cmd);
}
