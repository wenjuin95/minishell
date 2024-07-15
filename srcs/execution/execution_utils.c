/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:14:00 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/15 15:34:16 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief Close pipe file descriptors
*	@param pipefd: pipe file descriptor
*/
void	close_pipes(int	*pipefd)
{
	close(pipefd[PIPE_RD]);
	close(pipefd[PIPE_WR]);
}

/*
*	@brief Free redirection data
*	@param ptr: redirection data
*/
void	free_redir_data(void *ptr)
{
	t_redir_data	*data;

	data = (t_redir_data *)ptr;
	free(data->value);
	free(data);
}

/*
*	@brief Set file descriptor
*	@param data: redirection data
*	@note TOK_LESS [ < ]:: 0, O_RDONLY 
*	@note TOK_GREAT [ > ]:: 1, O_WRONLY | O_CREAT | O_TRUNC
*	@note TOK_DGREAT [ >> ]:: 1, O_WRONLY | O_CREAT | O_APPEND 
*	@note S_IRUSR: read permission for owner
*	@note S_IWUSR: write permission for owner
*	@note S_IRGRP: read permission for group
*	@note S_IROTH: read permission for others
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

#define HEREDOC_TEMP "/tmp/minishell_heredoc_temp" //temporary file for heredoc
#define ERRMSG_HEREDOC "heredoc delimited by end-of-file" //error message for heredoc

/*
*	@brief Set here_doc and read from input until delimiter
*	@param data: redirection data
*/
void	set_here_doc(t_redir_data *data)
{
	const mode_t	permissions = S_IRUSR | S_IWUSR;
	int				writefd;
	int				readfd;
	char			*line;
	char			*delimiter;

	writefd = open(HEREDOC_TEMP, O_WRONLY | O_CREAT | O_TRUNC, permissions);
	delimiter = data->value;
	if (writefd == -1)
		perror_exit("open");
	while (true)
	{
		line = readline("> ");
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		ft_putendl_fd(line, writefd);
		free(line);
	}
	close(writefd);
	readfd = open(HEREDOC_TEMP, O_RDONLY);
	dup2(readfd, STDIN_FILENO);
	close(readfd);
	unlink(HEREDOC_TEMP);
}
