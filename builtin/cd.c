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

#include "../minishell.h"

/*
*	handle cd command
*	1. cd
*	2. cd [any argument]
*/

//function to get the home directory
int	get_home_dir(char **env_storage)
{
	char *home;

	env_storage = add_or_replace_env(env_storage, "OLDPWD", 
		get_env_value(env_storage, "PWD")); //replace old pwd with current pwd
	home = get_env_value(env_storage, "HOME"); //get home directory value
	if (home == NULL)
	{
		ft_printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(home) == 0) //change to home directory
	{
		env_storage = add_or_replace_env(env_storage, "PWD", home); //replace pwd with home directory
		return (0);
	}
	return (1);
}

//function changing the current working directory with specified arguments.
int cd_option(char **env_storage, char **cmd)
{
	char *current;

	if (cmd[1] == NULL) //if no argument is given, change to home directory
		return (get_home_dir(env_storage));
	if (chdir(cmd[1]) == -1) //if the directory does not exist
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", cmd[1]);
		return (1);
	}
	env_storage = add_or_replace_env(env_storage, "OLDPWD", 
		get_env_value(env_storage, "PWD")); //replace old pwd with current pwd
	current = getcwd(NULL, 0); //get current working directory
	if (current == NULL)
		return (1);
	env_storage = add_or_replace_env(env_storage, "PWD", current); //replace pwd with current working directory
	free(current);
	return (0);
}
