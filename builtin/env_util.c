/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:30:22 by welow             #+#    #+#             */
/*   Updated: 2024/06/01 17:36:54 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//function to memory allocate for new environment variable
char	**malloc_env(char **env_storage, int len)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(len + 1, sizeof(char *));
	if (new_env == NULL)
		return (NULL);
	i = 0;
	while (env_storage[i])
	{
		new_env[i] = ft_strdup(env_storage[i]);
		if (new_env[i] == NULL)
		{
			free_2d(new_env);
			return (NULL);
		}
		i++;
	}
	return (new_env);
}

//function to get the index of the environment variable
/*
*	success: return the index of the environment variable
*	failure: return -1
*/
int	env_position(char **env_storage, char *env_var)
{
	int		i;

	if (env_var == NULL)
		return (-1);
	i = -1;
	while (env_storage[++i])
	{
		if (ft_strncmp(env_storage[i], env_var, ft_strlen(env_var)) == 0)
			return (i);
	}
	return (-1);
}

//TODO ::need redo
//function to add or replace environment variable
/*
*	success: return TRUE
*	failure: return FALSE
*/
char **add_or_replace_env(char **env_storage, char *name, char *value)
{
	int		pos;
	char	*new_value;

	pos = env_position(env_storage, name); //get the position
	if (value == NULL || *value == '\0')
		new_value = ""; //if no value, assign empty string
	else
		new_value = ft_strjoin("=", value); //if got value assign the value with "="
	if (pos == -1) //if position not found
	{
		char **new_env = malloc_env(env_storage, ft_2d_len(env_storage) + 1);
		if (new_env == NULL)
			return (NULL);
		new_env[ft_2d_len(env_storage)] = ft_strjoin(name, new_value);
		free_2d(env_storage);
		return (new_env);
	}
	else //if found then replace
	{
		free(env_storage[pos]); //if found, remove the old env variable
		env_storage[pos] = ft_strjoin(name, new_value); //assign the new env variable
		return (env_storage);
	}
}

//function found the env varible and remove it
/*
*	success: return TRUE
*	failure: return FALSE
*/
int	remove_env(char **env_storage, char *name)
{
	int		i;
	int		index;

	index = env_position(env_storage, name); //get the position
	if (index == -1) // if not found
		return (FALSE);
	free(env_storage[index]); //if found, free the memory
	i = index; //if found, get the position and assign to i
	while (env_storage[i+1]) //skip the removed env variable position and store the rest of the env variable
	{
		env_storage[i] = env_storage[i+1];
		i++;
	}
	env_storage[i] = NULL;
	return (TRUE);
}
