/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:14:00 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/08/16 23:46:09 by welow            ###   ########.fr       */
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
*	@param data redirection data
*	@param m_shell minishell struct
*	@param c_h current heredoc
*	@param t_h total heredoc
*	@return SUCCESS if no interrupt by SIGINT, FAIL if interrupted by SIGINT
*	@note 1. SIGINT make it exit the child process
*	@note 2. child process will create the here document
*	@note 3. if the child process interupted by the signal, it exit(FAIL);
*/
int	set_here_doc(t_redir_data *data, t_minishell *m_shell, int c_h, int t_h)
{
	bool	last_heredoc;

	last_heredoc = (c_h == t_h);
	m_shell->pid = fork();
	if (m_shell->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		create_here_doc_child(data);
		exit(FAIL);
	}
	else
		return (handle_heredoc_parent(m_shell, last_heredoc));
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
