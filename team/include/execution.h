/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:59:53 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/21 17:01:24 by welow            ###   ########.fr       */
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

typedef enum e_cmd_type
{
	CMD_EXEC,
	CMD_REDIR,
	CMD_PIPE,
}	t_cmd_type;

typedef struct s_cmd
{
	t_cmd_type	type;
}	t_cmd;

typedef struct s_redir_cmd
{
	t_cmd_type	type;
	char		*filename;
	mode_t		mode_flag;
	int			fd;
	t_cmd		*next_cmd;
}	t_redir_cmd;

typedef struct s_exec_cmd
{
	t_cmd_type	type;
	char		**argv;
}	t_exec_cmd;

typedef void	(*t_command)(t_cmd *);

void	eval_tree(t_cmd	*cmd);
void	command_execute(t_cmd *command);

#endif
