/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:26:24 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/03 18:47:36 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	eval_tree(t_cmd	*cmd);

void	command_execute(t_cmd *command)
{
	t_exec_cmd	*e_cmd;

	e_cmd = (t_exec_cmd *)command;
	if (fork() == 0)
	{
		ft_execvpe(e_cmd->argv[0], e_cmd->argv, environ);
		exit(127);
	}
	wait(0);
}

void	command_redirection(t_cmd *command)
{
	t_redir_cmd		*r_cmd;
	t_list			*curr;
	t_redir_data	*data;
	int				save[2];

	save[0] = dup(STDIN_FILENO);
	save[1] = dup(STDOUT_FILENO);
	r_cmd = (t_redir_cmd *)command;
	curr = r_cmd->redir_list;
	while (curr != NULL)
	{
		data = (t_redir_data *)curr->content;
		printf("Curr redir : %d %s\n", data->type, data->value);
		if (data->type == TOK_DLESS)
			printf("heredoc\n");
		else
			set_fd(data);
		curr = curr->next;
	}
	eval_tree(r_cmd->next_cmd);
	dup2(save[0], STDIN_FILENO);
	dup2(save[1], STDOUT_FILENO);
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
	[CMD_REDIR] = command_redirection
	};

	if (!cmd)
		return ;
	commands[cmd->type](cmd);
}
