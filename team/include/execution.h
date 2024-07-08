/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:59:53 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/08 15:32:34 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

/*
*	command function: function pointer to execute a command 
*	(t_command is a function pointer of the type void (t_cmd *))
*/
typedef void	(*t_command)(t_cmd *); 

enum e_pipefd //pipe file descriptor
{
	PIPE_RD = 0, //pipe read
	PIPE_WR = 1  //pipe write
};

//execvpe.c
void	ft_execvpe(const char *file, char *const argv[], char *const envp[]);

//execution.c
void	eval_tree(t_cmd	*cmd);
void	command_execute(t_cmd *command);

//execution_utils.c
void	close_pipes(int	*pipefd);
void	free_redir_data(void *ptr);
void	set_fd(t_redir_data *data);

#endif
