/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:59:53 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/03 13:48:34 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef void	(*t_command)(t_cmd *);

enum e_pipefd
{
	PIPE_RD = 0,
	PIPE_WR = 1
};

void	ft_execvp(const char *file, char *const argv[], char *const envp[]);

void	eval_tree(t_cmd	*cmd);
void	command_execute(t_cmd *command);

/* Exec Utils */

void	close_pipes(int	*pipefd);
void	free_redir_data(void *ptr);
void	set_fd(t_redir_data *data);

#endif
