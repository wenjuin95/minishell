/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:59:53 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/26 11:25:32 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "libft.h"
# include <unistd.h> //for execve
# include <stdio.h> //for perror
# include <fcntl.h> //for open
# include <sys/types.h> //for t_mode
# include <sys/stat.h> //for s_mode
// typedef unsigned short mode_t; // for window

typedef void	(*t_command)(t_cmd *);

void	eval_tree(t_cmd	*cmd);
void	command_execute(t_cmd *command);

#endif
