/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:59:11 by welow             #+#    #+#             */
/*   Updated: 2024/06/01 16:54:34 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <termios.h>
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
int		ft_2d_len(char **str);

//builtin
//echo.c :: handle echo argument (flag)
int		echo_option(char **cmd);
//pwd.c :: handle pwd command
int		pwd(char *cmd);
//env.c :: handle env command
char	**store_env(char **envp);
char	*get_env_value(char **env_storage, char *value);
void	print_environment(char **env_storage);
//env_util.c :: env utils 2
char	**malloc_env(char **env_storage, int len);
int		env_position(char **env_storage, char *env_var)
char	**add_or_replace_env(char **env_storage, char *name, char *value);
int		remove_env(char **env_storage, char *name);
//exit.c :: handle exit argument(flag)
int		exit_arg(char **cmd);
//cd.c :: handle cd argument(flag)
int		get_home_dir(char **env_storage);
int		cd_option(char **env_storage, char **cmd);
//export.c :: handle export argument(flag)
void	sort_env(char **env_storage);
char	**store_to_export(char **env_storage);
char	**store_option(char **env_storage, char **cmd);
char	**export_option(char **env_storage, char **cmd);

#endif