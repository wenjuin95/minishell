/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:14:00 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/02 21:41:12 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_open_info
{
	int	fd_to;
	int	flag;
}	t_open_info;

void	close_pipes(int	*pipefd)
{
	close(pipefd[PIPE_RD]);
	close(pipefd[PIPE_WR]);
}

void	free_redir_data(void *ptr)
{
	t_redir_data	*data;

	data = (t_redir_data *)ptr;
	free(data->value);
	free(data);
}

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
