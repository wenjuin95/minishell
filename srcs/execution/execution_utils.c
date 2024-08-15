/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:14:00 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/08/15 18:15:12 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief close the pipe file descriptor
*/
void	close_pipes(int	*pipefd)
{
	close(pipefd[PIPE_RD]);
	close(pipefd[PIPE_WR]);
}

/*
*	@brief free the redirection data
*/
void	free_redir_data(void *ptr)
{
	t_redir_data	*data;

	data = (t_redir_data *)ptr;
	free(data->value);
	free(data);
}

/*
*	@brief set the file descriptor before the command is executed(pipe or exe)
*/
void	set_fd(t_redir_data *data)
{
	const t_open_info	info[] = {
	[TOK_LESS] = {STDIN_FILENO, O_RDONLY},
	[TOK_GREAT] = {STDOUT_FILENO, O_WRONLY | O_CREAT | O_TRUNC},
	[TOK_DGREAT] = {STDOUT_FILENO, O_WRONLY | O_CREAT | O_APPEND}
	};
	const mode_t		permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int					fd;

	fd = open(data->value, info[data->type].flag, permissions);
	dup2(fd, info[data->type].fd_to);
}

/*
*	@brief set the here document
*	@note -ctrl + c make it exit the child process
*	@note -child process will create the here document
*	@note -parent process will read from the here document
*	@note -WIFEXITED: check if the child process exited normally
*	@note -WEXITSTATUS: get the exit status of the child process
*	@note -WINEXITED and WEXITSTATUS ,ust together if not it will cause 
*	       undefined behavior
*	@note -change_signal(false): default back the signal for parent process
*/
void	set_here_doc(t_redir_data *data, t_minishell *m_shell, int c_h, int t_h)
{
	int		readfd;
	bool	final_heredoc;

	final_heredoc = (c_h == t_h - 1);
	m_shell->pid = fork();
	if (m_shell->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		create_here_doc_child(data);
	}
	else
	{
		waitpid(m_shell->pid, &m_shell->status, 0);
		get_exit_code(m_shell);
		if (final_heredoc && WIFEXITED(m_shell->status)
			&& WEXITSTATUS(m_shell->status) == EXIT_SUCCESS)
		{
			readfd = open(HEREDOC_TEMP, O_RDONLY);
			dup2(readfd, STDIN_FILENO);
			close(readfd);
			unlink(HEREDOC_TEMP);
		}
	}
}

/*
*	@brief convert the linked list to array
*/
char	**list_to_array(t_list *list)
{
	char	**array;
	int		i;
	t_list	*curr;

	array = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	if (!array)
		perror_exit("malloc");
	i = 0;
	curr = list;
	while (curr)
	{
		array[i] = ft_strdup(curr->content);
		curr = curr->next;
		i++;
	}
	array[i] = NULL;
	ft_lstclear(&list, free);
	return (array);
}
