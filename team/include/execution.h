/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:59:53 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/02 21:38:50 by tkok-kea         ###   ########.fr       */
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

void	ft_execvpe(const char *file, char *const argv[], char *const envp[]);

void	eval_tree(t_cmd	*cmd);
void	command_execute(t_cmd *command);

/* Exec Utils */

void	close_pipes(int	*pipefd);
void	free_redir_data(void *ptr);
void	set_fd(t_redir_data *data);

#endif
