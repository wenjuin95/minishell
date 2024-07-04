/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:26:24 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/04 11:29:58 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	eval_tree(t_cmd	*cmd);

void	setup_redirections(t_list *redir_list)
{
	t_redir_data	*data;

	while (redir_list != NULL)
	{
		data = (t_redir_data *)redir_list->content;
		if (data->type == TOK_DLESS)
			printf("heredoc\n");
		else
			set_fd(data);
		redir_list = redir_list->next;
	}
}

void	command_execute(t_cmd *command)
{
	t_exec_cmd	*e_cmd;
	int			std_fds[3];

	e_cmd = (t_exec_cmd *)command;
	std_fds[0] = dup(STDIN_FILENO);
	std_fds[1] = dup(STDOUT_FILENO);
	std_fds[2] = dup(STDERR_FILENO);
	setup_redirections(e_cmd->redir_list);
	if (fork() == 0)
	{
		ft_execvpe(e_cmd->argv[0], e_cmd->argv, environ);
		exit(127);
	}
	wait(0);
	dup2(std_fds[0], STDIN_FILENO);
	dup2(std_fds[1], STDOUT_FILENO);
	dup2(std_fds[2], STDERR_FILENO);
}

void	command_pipe(t_cmd *cmd)
{
	t_pipe_cmd	*p_cmd;
	int			pipefd[2];

	p_cmd = (t_pipe_cmd *)cmd;
	if (pipe(pipefd) == -1)
		perror_exit("pipe");
	if (fork() == 0)
	{
		dup2(pipefd[PIPE_WR], STDOUT_FILENO);
		close_pipes(pipefd);
		eval_tree(p_cmd->left_cmd);
		exit(0);
	}
	if (fork() == 0)
	{
		dup2(pipefd[PIPE_RD], STDIN_FILENO);
		close_pipes(pipefd);
		eval_tree(p_cmd->right_cmd);
		exit(0);
	}
	close_pipes(pipefd);
	wait(0);
	wait(0);
}

/*
contains an lookup table(array) of functions
to execute when eval_tree() is called for a syntax tree node
*/
void	eval_tree(t_cmd	*cmd)
{
	const t_command	commands[] = {
	[CMD_EXEC] = command_execute,
	[CMD_PIPE] = command_pipe,
	};

	if (!cmd)
		return ;
	commands[cmd->type](cmd);
}
