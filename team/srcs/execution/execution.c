/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:26:24 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/04 10:59:50 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	eval_tree(t_cmd	*cmd);

/*
*	@brief Execute command
*	@param command Command to execute
*/
void	command_execute(t_cmd *command)
{
	t_exec_cmd	*e_cmd;

	ft_printf("command_execute\n"); //debug
	e_cmd = (t_exec_cmd *)command;
	if (fork() == 0)
	{
		ft_execvp(e_cmd->argv[0], e_cmd->argv, environ);
		exit(127); //command not found then return 127
	}
	wait(0);
}

/*
*	@brief redirection command
*	@param command Command to execute
*
*	@note 1. Redirection command contains a list of redirections
*	@note 2. Redirections are stored in a linked list
*	@note 3. Each redirection contains a type and a value
*	@note 4. Types are defined in scanner.h
*	@note 5. Values are the file names
*	@note 6. Permissions are set to read and write for owner, read for group and others
*	@note S_IRUSR : read permission, owner
*	@note S_IWUSR : write permission, owner
*	@note S_IRGRP : read permission, group
*	@note S_IROTH : read permission, others
*/
void	command_redirection(t_cmd *command)
{
	t_redir_cmd		*r_cmd;
	t_list			*curr;
	t_redir_data	*data;
	int				save[2];

	ft_printf("command_redirection\n"); //debug
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

/*
*	@brief pipe command
*	@param command Command to execute
*/
void	command_pipe(t_cmd *cmd)
{
	t_pipe_cmd	*p_cmd;
	int			pipefd[2];

	ft_printf("command_pipe\n"); //debug
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
