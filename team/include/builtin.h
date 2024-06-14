/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:10:31 by welow             #+#    #+#             */
/*   Updated: 2024/06/14 11:19:04 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_env_list
{
	char				*env_var;
	struct s_env_list	*next;
}	t_env_list;

//builtin
//builtin.c :: check if command is builtin
void	check_input(char **cmd, t_env_list *env_list);
//echo.c :: handle echo argument (flag)
int			echo_option(char **cmd);
//pwd.c :: handle pwd command(flag)
int			pwd_option(char **cmd);
//env.c :: handle env command(flag)
t_env_list	*store_env(char **envp);
void		print_env(t_env_list *env_list);
void		clear_env_list(t_env_list *env_list);
int			env_option(t_env_list *env_list, char **cmd);
//export.c :: handle export argument(flag)
void		sort_env(t_env_list *env_list);
void		print_export(t_env_list *env_list);
int			check_name_exist(t_env_list *env_list, char *env_var);
void		check_and_update_env(t_env_list *env_list, char *env_var);
int 		export_option(t_env_list *env_list, char **cmd);
//export_utils.c :: utility function for export
char		*get_name(char *env_var);
char		*get_value(char *env_var);
void		replace_env_var(t_env_list *env_list, char *new_var);
void		add_env_var(t_env_list *env_list, char *new_var);
char		*ft_join_env(char *name, char *value);
//unset.c :: handle unset argument(flag)
void		remove_env_var(t_env_list *env_list, char *cmd);
int			unset_option(t_env_list *env_list, char **cmd);


# endif
