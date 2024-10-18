/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:56:34 by welow             #+#    #+#             */
/*   Updated: 2024/07/31 13:56:34 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief create a left child process
*	@param pipefd file descriptor for pipe
*	@param cmd command to be executed
*	@param m_shell minishell struct and the m_shell->pid
* 	@note -ignore the signal for SIGINT and SIGQUIT when write to pipe
*	(to prevent interrupt by the signal when write to the pipe)
*/
void	create_left_child(int pipefd[2], t_cmd *cmd, t_minishell *m_shell)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	m_shell->pid_left = fork();
	if (m_shell->pid_left == 0)
	{
		dup2(pipefd[PIPE_WR], STDOUT_FILENO);
		close_pipes(pipefd);
		eval_tree(cmd, m_shell);
		exit(m_shell->exit_code);
	}
}

/*
*	@brief create a right child process
*	@param pipefd file descriptor for pipe
*	@param cmd command to be executed
*	@param m_shell minishell struct and the m_shell->pid
* 	@note -ignore the signal for SIGINT and SIGQUIT when read from pipe
*	(to prevent interrupt by the signal when read from the pipe)
*/
void	create_right_child(int pipefd[2], t_cmd *cmd, t_minishell *m_shell)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	m_shell->pid_right = fork();
	if (m_shell->pid_right == 0)
	{
		dup2(pipefd[PIPE_RD], STDIN_FILENO);
		close_pipes(pipefd);
		eval_tree(cmd, m_shell);
		exit(m_shell->exit_code);
	}
}

/*
*	@brief get the exit code from the child process
*	@param m_shell get the status from waitpid
*	@note -WIFFSIGNALED: if the child process was terminated by signal
*	@note -WTERMSIG: return the signal number (is either SIGINT(2) or SIGQUIT(3))
*	@note -WEXITSTATUS: return the exit status of the child process
*/
void	get_exit_code(t_minishell *m_shell)
{
	if (WIFSIGNALED(m_shell->status))
		m_shell->exit_code = WTERMSIG(m_shell->status) + 128;
	else
		m_shell->exit_code = WEXITSTATUS(m_shell->status);
}

/*
*	@brief handle new shell signal
*	@param new_shell check if the command is new shell
*	@note 1. if new shell, then ignore all the signal
*	(to prevent interrupt by the signal when first start the minishell)
*	@note 2. if not new shell, then change the signal for child process
*/
static void	set_new_shell_signal(bool new_shell)
{
	if (new_shell == true)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
		change_signal(true);
}

/*
*	@brief execute the command
*	@param argv argument to pass in
*	@param m_shell minishell struct
*	@param status is the status of the redirection if it fails 
*				  the command will also fail
*	@note 1. if the status is FAIL, then exit with status 130 without
*			 executing the command
*	@note 2. if the status is SUCCESS, then execute the command
*	@note 3. if ft_strcmp is 0 mean "true" not "0"
*	@note 4. the
*/
void	handle_execution(char **argv, t_minishell *m_shell, int status)
{
	bool	new_shell;

	new_shell = ft_strcmp(argv[0], "./minishell") == 0;
	m_shell->pid = fork();
	if (m_shell->pid == 0)
	{
		set_new_shell_signal(new_shell);
		if (status == FAIL)
			exit(CTRL_C);
		ft_execvpe(argv[0], argv, m_shell->env_storage);
		ft_clean(m_shell);
		exit(COMMAND_NOT_FOUND);
	}
	set_new_shell_signal(new_shell);
	(waitpid(m_shell->pid, &m_shell->status, 0), get_exit_code(m_shell));
	reset_std_fds(m_shell);
	change_signal(false);
}
