/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:14:00 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/08 15:37:09 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_open_info //open file information
{
	int	fd_to; //file descriptor to
	int	flag;  //flag: O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC, O_APPEND
}	t_open_info;

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
	@note 0 is stdin and 1 is stdout
	@note TOK_LESS [ < ]:: 0, O_RDONLY 
	@note TOK_GREAT [ > ]:: 1, O_WRONLY | O_CREAT | O_TRUNC
	@note TOK_DGREAT [ >> ]:: 1, O_WRONLY | O_CREAT | O_APPEND 
	@note S_IRUSR: read permission for owner
	@note S_IWUSR: write permission for owner
	@note S_IRGRP: read permission for group
	@note S_IROTH: read permission for others
*/
void	set_fd(t_redir_data *data)
{
	const t_open_info	info[] = {
	[TOK_LESS] = {0, O_RDONLY},
	[TOK_GREAT] = {1, O_WRONLY | O_CREAT | O_TRUNC},
	[TOK_DGREAT] = {1, O_WRONLY | O_CREAT | O_APPEND}
	};
	const mode_t		permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int					fd;

	fd = open(data->value, info[data->type].flag, permissions);
	dup2(fd, info[data->type].fd_to);
}
