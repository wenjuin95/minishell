/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:59:11 by welow             #+#    #+#             */
/*   Updated: 2024/06/23 15:47:38 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"

# include <signal.h>
# include "libft.h"

# define TRUE 1
# define FALSE 0
# define PROMPT "\033[1;32mminishell:\033[0m " 
# define ARROW " \033[1;33m>\033[0m "


//env in link list
typedef struct s_env_lst
{
	char				*name;
	char				*value;
	struct s_env_lst	*next;
}	t_env_lst;

//struct for minishell
typedef struct s_minishell
{
	char		*cmd;
	char		**split_cmd;
	int			exit_code;
	char		**env_storage;
	t_env_lst	*env_lst;
}	t_minishell;

extern t_minishell	m_shell;

//signal.c :: handle signal
void		handle_ctrl_c(int signum);
void		handle_signal(void);

// //execute.c :: execute command
// char		*get_path(char **cmd, char**env_storage);
// void		execute_cmd(char *input, char **env_storage);

//utils.c
void		free_2d(char **str);
void		*memory_manage(void *ptr, int clean);
void		ft_clean(int clean_cmd);

//builtin
//echo.c :: handle echo argument (flag) [done]
int			echo_option(char **cmd);
//pwd.c :: handle pwd command(flag) [done]
int			pwd_option(char **cmd);
//env.c :: handle env command(flag)
char		*get_name(char *env_var);
char		*get_value(char *env_var);
void		store_env(void);
int			env_option(char **cmd);
//env_utils.c :: utility function for env
t_env_lst	*ft_env_new(char *name, char *value);
void		ft_env_add_back(t_env_lst *new);
void		update_env_lst(char *name, char *value, int add);
// //export.c :: handle export argument(flag)
void		print_export(void);
int			check_alphanum(char *cmd);
int			check_name_exist(char *name);
int			export_option(char **cmd);
// //exit.c :: handle exit argument(flag)
void		exit_option(char **cmd);
// // //cd.c :: handle cd argument(flag)
char		*get_envlst_value(char *name);
int			cd_option(char **cmd);
// //unset.c :: handle unset argument(flag)
int			unset_option(char **cmd);

#endif