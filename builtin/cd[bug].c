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

//function search the variable in the env list and get the value
static char	*search_env_value(t_env_list *env_list, char *name)
{
	t_env_list	*current;

	current = env_list;
	while (current != NULL)
	{
		if (ft_strncmp(current->env_name, name,
				ft_strlen(current->env_name)) == 0)
			return (ft_strdup(current->env_value));
		current = current->next;
	}
	return NULL; // Return NULL if the environment variable is not found
}

//function to get the home directory
int	get_home_dir(t_env_list *env_list)
{
	char		*home;
	t_env_list	*current;

	current = env_list;
	replace_env_var(current, ft_strjoin("OLDPWD=",
			search_env_value(current, "PWD"))); //replace old pwd with current pwd
	home = search_env_value(current, "HOME"); //get the home directory value
	if (home == NULL)
	{
		ft_printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(home) == 0) //change to home directory
	{
		replace_env_var(current, ft_strjoin("PWD=", home)); //replace pwd with home directory
		return (0);
	}
	return (1);
}

//function changing the current working directory with specified arguments.
int	cd_option(t_env_list *env_list, char **cmd)
{
	char		*current_dir;
	t_env_list	*current;
	int			i;

	current = env_list;
	i = 1;
	if (cmd[i] == NULL) //if no argument is given, change to home directory
		return (get_home_dir(current));
	if (chdir(cmd[i]) == -1) //if the directory does not exist
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", cmd[i]);
		return (1);
	}
	else //if directory exist
	{
		replace_env_var(current, ft_strjoin("OLDPWD=", search_env_value(current, "PWD"))); //replace old pwd with current pwd
		current_dir = getcwd(NULL, 0); //get current working directory value
		if (current_dir == NULL)
			return (1);
		update_env_var(current, "PWD", current_dir); //replace pwd with current working directory
		free(current_dir);
		return (0);
	}
}
