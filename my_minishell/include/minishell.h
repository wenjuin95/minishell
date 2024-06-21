/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:59:11 by welow             #+#    #+#             */
/*   Updated: 2024/06/21 23:16:37 by welow            ###   ########.fr       */
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
typedef struct s_env_list
{
	char				*env_var;
	struct s_env_list	*next;
}	t_env_list;

//struct for minishell
typedef struct s_minishell
{
	char	*cmd;
	char	**split_cmd;
	int		exit_code;
	t_env_list	*env_list;
}	t_minishell;

//signal.c :: handle signal
void		handle_ctrl_c(int signum);
void		handle_signal(void);

// //execute.c :: execute command
// char		*get_path(char **cmd, char**env_storage);
// void		execute_cmd(char *input, char **env_storage);

//utils.c
void		free_2d(char **str);
// void		ft_clean_cmd(t_minishell m_shell, int clean_env);
void		ft_clean(t_minishell m_shell, int c_split, int c_env);

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
// //cd.c :: handle cd argument(flag) [bug]
char 		*search_env_value(t_env_list *env_list, char *env_name);
int			get_err(char *cmd);
int			main_dir(t_env_list *env_list, char *home_value, char *pwd_value);
int			chg_pwd(t_env_list *env_list);
int			cd_option(t_env_list *env_list, char **cmd);
//unset.c :: handle unset argument(flag) [done]
void		remove_env_var(t_env_list *env_list, char *cmd);
int			unset_option(t_env_list *env_list, char **cmd);
// //exit.c :: handle exit argument(flag) [done]
void		exit_option(t_minishell m_shell, char **cmd);

#endif