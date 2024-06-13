/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:59:11 by welow             #+#    #+#             */
/*   Updated: 2024/06/13 14:09:59 by welow            ###   ########.fr       */
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
# define PROMPT "\033[0;32mminishell:\033[0m " 
# define ARROW " \033[0;32m>\033[0m "


//TODO :: env link_list??
typedef struct s_env_list
{
	char				*env_var;
	struct s_env_list	*next;
}	t_env_list;

//struct for minishell
typedef struct s_minishell
{
	char	*cmd;
	char	**split_word;
}	t_minishell;

//signal.c :: handle signal
void		handle_ctrl_c(int signum);
void		handle_signal(void);

//execute.c :: execute command
char		*get_path(char **cmd, char**env_storage);
void		execute_cmd(char *input, char **env_storage);

//utils.c
void		free_2d(char **str);
int			ft_2d_len(char **str);

//builtin
//echo.c :: handle echo argument (flag) [done]
int			echo_option(char **cmd);
//pwd.c :: handle pwd command(flag) [done]
int			pwd_option(char **cmd);
//env.c :: handle env command(flag) [done]
t_env_list	*store_env(char **envp);
void		print_env(t_env_list *env_list);
void		clear_env_list(t_env_list *env_list);
int			env_option(t_env_list *env_list, char **cmd);
//export.c :: handle export argument(flag)[done]
void		sort_env(t_env_list *env_list);
void		print_export(t_env_list *env_list);
int			check_name_exist(t_env_list *env_list, char *env_var);
void		check_and_update_env(t_env_list *env_list, char *env_var);
int 		export_option(t_env_list *env_list, char **cmd);
//export_utils.c :: utility function for export [done]
char		*get_name(char *env_var);
char		*get_value(char *env_var);
void		replace_env_var(t_env_list *env_list, char *new_var);
void		add_env_var(t_env_list *env_list, char *new_var);
char		*ft_join_env(char *name, char *value);
// //exit.c :: handle exit argument(flag) [done]
// void			exit_option(char **cmd);
// //cd.c :: handle cd argument(flag) [bug]
// int			get_home_dir(t_env_list *env_list);
// int			cd_option(t_env_list *env_list, char **cmd);
//unset.c :: handle unset argument(flag) [done]
// int			remove_env_var(t_env_list *env_list, char *name);
// int			unset_option(t_env_list *env_list, char **cmd);

#endif