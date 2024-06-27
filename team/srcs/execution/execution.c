/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:26:24 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/27 14:36:20 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	eval_tree(t_cmd	*cmd);

void	command_execute(t_cmd *command)
{
	t_exec_cmd	*e_cmd;
	pid_t		pid;

	e_cmd = (t_exec_cmd *)command;
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)
	{
		ft_execvp(e_cmd->argv[0], e_cmd->argv, environ);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
}

void	command_redirection(t_cmd *command)
{
	t_redir_cmd		*r_cmd;
	const mode_t	permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	r_cmd = (t_redir_cmd *)command;
	close(r_cmd->fd);
	if (open(r_cmd->filename, r_cmd->mode_flag, permissions) < 0)
		perror("open");
	eval_tree(r_cmd->next_cmd);
}

// void	command_pipe(t_cmd *cmd)
// {
// 	t_pipe_cmd	*p_cmd;
// 	int			pipefd[2];

// 	p_cmd = (t_pipe_cmd *)cmd;
// 	if (pipe(pipefd) == -1)
// 		perror_exit("pipe");
// 	if (fork() == 0)
// 	{
// 		dup2(pipefd[PIPE_WR], STDOUT_FILENO);
// 		close(pipefd[PIPE_RD]);
// 		close(pipefd[PIPE_WR]);
// 		eval_tree(p_cmd->left_cmd);
// 	}
// 	else
// 	{
// 		dup2(pipefd[PIPE_RD], STDIN_FILENO);
// 		close(pipefd[PIPE_RD]);
// 		close(pipefd[PIPE_WR]);
// 		eval_tree(p_cmd->right_cmd);
// 	}
// }

/*
contains an lookup table(array) of functions
to execute when eval_tree() is called for a syntax tree node
*/
void	eval_tree(t_cmd	*cmd)
{
	const t_command	commands[] = {
	[CMD_EXEC] = command_execute,
	// [CMD_PIPE] = command_pipe,
	[CMD_REDIR] = command_redirection
	};

	commands[cmd->type](cmd);
}
