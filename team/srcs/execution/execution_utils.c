/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:14:00 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/02 12:07:16 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief Close all pipe file descriptors
*	@param pipefd Pipe file descriptors
*/
void	close_pipes(int	*pipefd)
{
	close(pipefd[PIPE_RD]);
	close(pipefd[PIPE_WR]);
}

/*
*	@brief Free redirection data
*	@param ptr Redirection data
*/
void	free_redir_data(void *ptr)
{
	t_redir_data	*data;

	data = (t_redir_data *)ptr; //cast to t_redir_data
	free(data->value);
	free(data);
}
