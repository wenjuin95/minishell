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
	int		len;
	int		env_len;
	int		i;

	env_len = -1;
	while (envp[++env_len]); //get the length of envp
	// //testing the envp length
	// ft_printf("lenght of envp: %d\n\n", env_len);
	env_storage = (char **)malloc(sizeof(char *) * (env_len + 1));
	if (env_storage == NULL)
	{
		printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}

	//copy the envp to env_storage
	i = -1;
	while (envp[++i])
	{
		len = ft_strlen(envp[i]) + 1; //get the length of the string
		env_storage[i] = ft_calloc(len, sizeof(char)); //allocate memory for the string
		ft_strlcpy(env_storage[i], envp[i], len);
	}
	return (env_storage);
}