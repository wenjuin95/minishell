/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:59:45 by welow             #+#    #+#             */
/*   Updated: 2024/05/27 13:59:45 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	TODO:
*	1. cd
*	2. cd [any argument]
*/

// /*
// *	@brief get value from env_lst with the name
// *	@param name name of the environment variable
// *	@return value of the environment variable you looking for
// */
// char	*get_envlst_value(char *name)
// {
// 	t_env_lst	*current;

// 	current = m_shell.env_lst;
// 	while (current)
// 	{
// 		if (ft_strncmp(name, current->name, ft_strlen(name)) == 0)
// 			return (current->value);
// 		current = current->next;
// 	}
// 	return (NULL);
// }

// /*
// *	@brief update PWD to the current directory
// */
// static int	chg_pwd(void)
// {
// 	char	*pwd;

// 	pwd = getcwd(NULL, 0);
// 	if (pwd == NULL)
// 		return (1);
// 	update_env_lst("PWD", pwd, FALSE); //update PWD
// 	return (0);
// }

// /*
// *	@brief change to main directory
// */
// static int	main_dir(void)
// {
// 	char	*home;

// 	update_env_lst("OLDPWD", get_envlst_value("PWD"), FALSE); //update OLDPWD
// 	home = get_envlst_value("HOME");
// 	if (home == NULL)
// 	{
// 		printf("minishell: cd: HOME not set\n");
// 		return (1);
// 	}
// 	if (chdir(home) == 0) //if success
// 	{
// 		update_env_lst("PWD", home, FALSE); //update PWD
// 		return (0);
// 	}
// 	return (1);
// }

// /*
// *	@brief change to the previous directory
// */
// static int	return_dir(void)
// {
// 	if (get_envlst_value("OLDPWD") == NULL)
// 	{
// 		printf("minishell: cd: OLDPWD not set\n");
// 		return (1);
// 	}
// 	if (chdir(get_envlst_value("OLDPWD")) == 0) //if success
// 	{
// 		update_env_lst("PWD", get_envlst_value("OLDPWD"), FALSE); //update PWD
// 		return (0);
// 	}
// 	return (1);
// }

// int	cd_option(char **cmd)
// {
// 	int	i;

// 	i = 1;
// 	if (cmd[i] == NULL || cmd[i][0] == '~') //cd no argument
// 		return (main_dir());
// 	if (cmd[i][0] == '-') //"cd -" option
// 		return (return_dir());
// 	if (chdir(cmd[i]) == -1) //if no such file or directory
// 	{
// 		printf("minishell: cd: %s: No such file or directory\n", cmd[i]);
// 		return (1);
// 	}
// 	update_env_lst("OLDPWD", get_envlst_value("PWD"), FALSE); //update OLDPWD
// 	return (chg_pwd()); //update PWD
// }
