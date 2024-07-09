/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:26:24 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/09 11:05:26 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this is a global variable for this file
extern char	**environ;

void	eval_tree(t_cmd	*cmd, t_minishell *m_shell);

/*
*	@brief set file descriptor for redirection data
*	@param data: redirection data
*/
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


void	reset_std_fds(t_minishell *m_shell)
{
	dup2(m_shell->std_fds[STDIN_FILENO], STDIN_FILENO);
	dup2(m_shell->std_fds[STDOUT_FILENO], STDOUT_FILENO);
	dup2(m_shell->std_fds[STDERR_FILENO], STDERR_FILENO);
}

/*
*	@brief execute a command
*	@param command: command node in the syntax tree
*	@param m_shell: to get env_storage from minishell struct
*/
void	command_execute(t_cmd *command, t_minishell *m_shell)
{
	t_exec_cmd	*e_cmd;

	e_cmd = (t_exec_cmd *)command;
	setup_redirections(e_cmd->redir_list);
	if (fork() == 0)
	{
		ft_execvpe(e_cmd->argv[0], e_cmd->argv, m_shell->env_storage);
		exit(127);
	}
	wait(0);
	reset_std_fds(m_shell);
}

/*
*	@brief execute a command with pipe
*	@param cmd: command node in the syntax tree
*/
void	command_pipe(t_cmd *cmd, t_minishell *m_shell)
{
	t_pipe_cmd	*p_cmd;
	int			pipefd[2];

	p_cmd = (t_pipe_cmd *)cmd;
	if (pipe(pipefd) == -1)
		perror_exit("pipe");
	if (fork() == 0) //child process of pipe tht writes to pipe
	{
		dup2(pipefd[PIPE_WR], STDOUT_FILENO);
		close_pipes(pipefd);
		eval_tree(p_cmd->left_cmd, m_shell);
		exit(0);
	}
	if (fork() == 0) //child process of pipe that reads from pipe
	{
		dup2(pipefd[PIPE_RD], STDIN_FILENO);
		close_pipes(pipefd);
		eval_tree(p_cmd->right_cmd, m_shell);
		exit(0);
	}
	close_pipes(pipefd); //close all pipe file descriptors
	wait(0); //wait for child process that writes to pipe to finish
	wait(0); //wait for child process that reads from pipe to finish
}

/*
*	@brief contains an lookup table(array) of functions 
	to execute when eval_tree() is called for a syntax tree node
	@param cmd: command node in the syntax tree
*/
void	eval_tree(t_cmd	*cmd, t_minishell *m_shell)
{
	const t_command	commands[] = {
	[CMD_EXEC] = command_execute,
	[CMD_PIPE] = command_pipe,
	};

	if (!cmd) //if command is NULL, return nothing
		return ;
	commands[cmd->type](cmd, m_shell); //this will call the function in the lookup table
}

void	execute(t_minishell *m_shell)
{
	eval_tree(m_shell->syntax_tree, m_shell);
}