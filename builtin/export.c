/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:10:25 by welow             #+#    #+#             */
/*   Updated: 2024/05/31 14:22:36 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//function to print all the environment variables with "declare -x"
/*
* TODO:
* 0. create a export list
* 1. print all env after "declare -x"
* 2. must be sorted
* 3. new variable will go to the export list
* 4. export AAA=abc -> env_storage
* 5. export -> print all env in export list
* 6. export AAA -> export_storage
*/

void	sort_env(char **env_storage)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	i = 0;
	len = ft_2d_len(env_storage);
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(env_storage[i], env_storage[j],
					ft_strlen(env_storage[i])) > 0)
			{
				temp = env_storage[i];
				env_storage[i] = env_storage[j];
				env_storage[j] = temp;
			}
			j++;
		}
		i++;
	}
}

//function store the environment variables to export
char	**store_to_export(char **env_storage)
{
	int	i;

	sort_env(env_storage);
	i = 0;
	while (env_storage[i])
	{
		env_storage[i] = ft_strjoin("declare -x ", env_storage[i]);
		i++;
	}
	return (env_storage);
}

//function either store at env_storage or export storage
char	**store_option(char **env_storage, char **cmd)
{
	int		i;
	char	**tmp_env;

	i = 1;
	while (cmd[i] != NULL)
	{
		if (ft_strchr(cmd[i], '=') != NULL) //if the variable had value
		{
			tmp_env = ft_split(cmd[i], '=');
			env_storage = add_or_replace_env(env_storage, tmp_env[0],
					tmp_env[1]);
			free_2d(tmp_env);
		}
		else //if the variable no value
		{
			env_storage = add_or_replace_env(env_storage, cmd[i], "");
			env_storage = store_to_export(env_storage);
		}
		i++;
	}
	return (env_storage);
}

//function for export command
char **export_option(char **env_storage, char **cmd)
{
	int		i;

	i = 1;
	if (cmd[i] == NULL) //env list + [declare -x] to export list
		return (store_to_export(env_storage));
	else //add the new env to the export list
	{
		env_storage = store_option(env_storage, cmd);
		return (env_storage);
	}
}
