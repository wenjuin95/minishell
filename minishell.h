/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:59:11 by welow             #+#    #+#             */
/*   Updated: 2024/05/23 14:10:22 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"
// # include <readline/readline.h>
// # include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include "./libft/libft.h"

# define TRUE 1
# define FALSE 0

//signal.c :: handle signal
void	handle_ctrl_c(int signum);
void	handle_signal(void);


//execute.c :: execute command
char	*get_path(char **cmd, char**env_storage);
void	execute_cmd(char *input, char **env_storage);

//utils.c
void	free_2d(char **str);

//builtin
//echo.c :: handle echo command (flag)
int		echo_option(char **cmd);
//pwd.c :: handle pwd command
int		pwd(char *cmd);
//env.c :: store environment variable
char	**store_env(char **envp);
void	print_environment(char **env_storage);
//exit.c :: handle exit command (flag)
void	exit_cmd(char **cmd);




#endif