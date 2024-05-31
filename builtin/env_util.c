/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:30:22 by welow             #+#    #+#             */
/*   Updated: 2024/05/31 15:49:39 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//function to memory allocate for new environment variable
char	**add_env(char **env_storage, int len)
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
int	env_index(char **env_storage, char *name)
{
	int		i;
	char	*env_name;

	env_name = ft_strjoin(name, "=");
	if (env_name == NULL)
		return (-1);
	i = -1;
	while (env_storage[++i])
	{
		if (ft_strncmp(env_storage[i], env_name, ft_strlen(env_name)) == 0)
		{
			free(env_name);
			return (i);
		}
	}
	free(env_name);
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
    int		index;
    char	*env_value;

    index = env_index(env_storage, name);
    if (value == NULL || *value == '\0')
        env_value = ft_strdup("");
	else
    	env_value = ft_strjoin("=", value); //join value with "="
    if (env_value == NULL)
        return (env_storage);
    if (index != -1 && env_storage[index] != NULL)        //replace existing env variable
    {
        free(env_storage[index]);
        env_storage[index] = ft_strjoin(name, env_value); // join name with value
    }
    else         //add new env variable
    {
        index = ft_2d_len(env_storage);
        env_storage = add_env(env_storage, index+1); //add new env variable
        if (env_storage == NULL)
            return (NULL);
        env_storage[index] = ft_strjoin(name, env_value); //join name with value
    }
    free(env_value);
    return (env_storage);
}

//function to remove environment variable
/*
*	success: return TRUE
*	failure: return FALSE
*/
int	remove_env(char **env_storage, char *name)
{
	int		i;
	int		len;
	int		index;

	index = env_index(env_storage, name);
	if (index == -1)
		return (FALSE);
	free(env_storage[index]);
	i = index;
	len = index;
	while (env_storage[i+1]) //skip the removed env variable to store the rest of the env variable
	{
		env_storage[i] = ft_strdup(env_storage[i+1]);
		free(env_storage[i+1]);
		i++;
		len++;
	}
	env_storage[len] = NULL;
	return (TRUE);
}
