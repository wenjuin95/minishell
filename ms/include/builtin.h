/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:10:31 by welow             #+#    #+#             */
/*   Updated: 2024/10/18 13:36:57 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_env_lst
{
	char				*name;
	char				*value;
	struct s_env_lst	*next;
}	t_env_lst;

typedef struct s_minishell	t_minishell;

//builtin.c :: check the input is builtin or not
bool		check_input(char *cmd);
void		execute_input(t_minishell *m_shell, char **cmd);

//echo.c :: handle echo argument (flag)
int			echo_option(char **cmd, t_minishell *m_shell);

//pwd.c :: handle pwd command(flag)
int			pwd_option(char **cmd, t_minishell *m_shell);

//env.c :: handle env command(flag)
char		*get_name(char *env_var);
char		*get_value(char *env_var);
void		store_env(t_minishell *m_shell);
int			env_option(char **cmd, t_minishell *m_shell);

//env_utils.c :: utility function for env
bool		check_name_exist(char *name, t_minishell *m_shell);
t_env_lst	*ft_env_new(char *name, char *value);
void		ft_env_add_back(t_minishell *m_shell, t_env_lst *new);
void		update_env(char *name, char *value, bool add, t_minishell *m_shell);

// //export.c :: handle export argument(flag)
void		print_export(t_minishell *m_shell);
bool		check_alphanum(char *cmd);
int			export_option(char **cmd, t_minishell *m_shell);

// //export_utils.c :: utility function for export
t_env_lst	*copy_list(t_env_lst *head);
void		sort_list(t_env_lst **head);
void		free_copy(t_env_lst *head);

//exit.c :: handle exit argument(flag)
void		exit_option(char **cmd, t_minishell *m_shell);

// // // //cd.c :: handle cd argument(flag)
char		*get_envlst_value(char *name, t_minishell *m_shell);
int			cd_option(char **cmd, t_minishell *m_shell);

//unset.c :: handle unset argument(flag)
void		remove_env_var(t_minishell *m_shell, char *name);
int			unset_option(char **cmd, t_minishell *m_shell);

#endif
