/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:59:53 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/15 15:32:21 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

enum e_pipefd //pipe file descriptor
{
	PIPE_RD = 0, //pipe read
	PIPE_WR = 1  //pipe write
};

typedef struct s_open_info //open file info
{
	int	fd_to; //file descriptor to
	int	flag; //flag for open
}	t_open_info;

//execvpe.c
void	ft_execvpe(const char *file, char *const argv[], char *const envp[]);

//execution_utils.c
void	close_pipes(int	*pipefd);
void	free_redir_data(void *ptr);
void	set_fd(t_redir_data *data);
void	set_here_doc(t_redir_data *data);

#endif
