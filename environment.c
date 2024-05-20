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

#include "minishell.h"

char **store_env(char **envp)
{
	char	**env_storage;
	int		env_len;
	int		i;

	env_len = -1;
	while (envp[++env_len]); //get the length of envp
	// //test: the envp length
	//ft_printf("lenght of envp: %d\n\n", env_len);
	env_storage = (char **)malloc(sizeof(char *) * (env_len + 1));
	if (env_storage == NULL)
	{
		printf("malloc failed\n");
		free_2d(env_storage);
		exit(EXIT_FAILURE);
	}

	//copy the envp to env_storage
	i = -1;
	while (envp[++i])
	{
		env_storage[i] = ft_strdup(envp[i]);
		if (env_storage[i] == NULL)
		{
			free_2d(env_storage);
			return NULL;
		}
	}
	env_storage[i] = NULL;
	return (env_storage);
}

void print_environment(char **env_storage)
{
	int	i;

	i = -1;
	while (env_storage[++i])
		ft_printf("%s\n", env_storage[i]);
	// //test :: the total env
	// ft_printf("total env: %d\n", i);
}