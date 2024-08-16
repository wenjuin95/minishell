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
	m_shell->pid = fork();
	if (m_shell->pid == 0)
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
	m_shell->pid2 = fork();
	if (m_shell->pid2 == 0)
	{
		dup2(pipefd[PIPE_RD], STDIN_FILENO);
		close_pipes(pipefd);
		eval_tree(cmd, m_shell);
		exit(m_shell->exit_code);
	}
}

/*
*	@brief create a child process for here document
*	@param data redirection data
*/
void	create_here_doc_child(t_redir_data *data)
{
	const mode_t	permissions = S_IRUSR | S_IWUSR;
	int				writefd;
	char			*line;
	char			*delimiter;

	writefd = open(HEREDOC_TEMP, O_WRONLY | O_CREAT | O_TRUNC, permissions);
	delimiter = data->value;
	if (writefd == -1)
		perror_exit("open");
	while (true)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, delimiter) == 0)
			break ;
		ft_putendl_fd(line, writefd);
		free(line);
	}
	close(writefd);
	exit(EXIT_SUCCESS);
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
*	@brief not minishell then execute the command else create a new minishell
*	@param argv argument to pass in
*	@param m_shell minishell struct
*	@note -if create minishell, then ignore all the signal
*	(to prevent interrupt by the signal when first start the minishell)
*	@note -if not minishell, then change the signal for child process
*/
void	handle_new_minishell(char **argv, t_minishell *m_shell, int status)
{
	if (ft_strncmp(argv[0], "./minishell", 11) == 0)
	{
		(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN));
		m_shell->pid = fork();
		if (m_shell->pid == 0)
			(ft_execvpe(argv[0], argv, m_shell->env_storage), exit(127));
		(waitpid(m_shell->pid, &m_shell->status, 0), get_exit_code(m_shell));
		reset_std_fds(m_shell);
	}
	else
	{
		change_signal(true);
		m_shell->pid = fork();
		if (m_shell->pid == 0)
		{
			if (status == FAIL)
				exit(130);
			(ft_execvpe(argv[0], argv, m_shell->env_storage), exit(127));
		}
		(waitpid(m_shell->pid, &m_shell->status, 0), get_exit_code(m_shell));
		reset_std_fds(m_shell);
	}
}
