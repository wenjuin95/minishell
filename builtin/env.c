/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:32:25 by welow             #+#    #+#             */
/*   Updated: 2024/05/17 16:32:25 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 *	handle env command
 *	1. env
 */

//function to store environment variable to env_storage
char	**store_env(char **envp)
{
	char	**env_storage;
	int		env_len;
	int		i;

	env_len = -1;
	while (envp[++env_len]); //get the length of envp
	env_storage = (char **)malloc(sizeof(char *) * (env_len + 1));
	if (env_storage == NULL)
	{
		printf("malloc failed\n");
		free_2d(env_storage);
		exit(EXIT_FAILURE);
	}
	i = -1;	//copy the envp to env_storage
	while (envp[++i])
	{
		env_storage[i] = ft_strdup(envp[i]);
		if (env_storage[i] == NULL)
		{
			free_2d(env_storage);
			return (NULL);
		}
	}
	env_storage[i] = NULL;
	return (env_storage);
}

//function to print environment variable
void	print_environment(char **env_storage)
{
	int	i;

	i = -1;
	while (env_storage[++i])
		ft_printf("%s\n", env_storage[i]);
}

//function to get the environment variable value
char *get_env_value(char **env_storage, char *value)
{
	int		i;

	i = -1;
	while (env_storage[++i])
	{
		if (ft_strncmp(env_storage[i], value, ft_strlen(value)) == 0)
		{
			value = ft_strchr(env_storage[i], '=') + 1;
			return (value);
		}
	}
	return (NULL);
}