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

// //function to store environment variable to env_storage
// char	**store_env(char **envp)
// {
// 	char	**env_storage;
// 	int		env_len;
// 	int		i;

// 	env_len = -1;
// 	while (envp[++env_len]); //get the length of envp
// 	env_storage = (char **)malloc(sizeof(char *) * (env_len + 1));
// 	if (env_storage == NULL)
// 	{
// 		printf("malloc failed\n");
// 		free_2d(env_storage);
// 		exit(EXIT_FAILURE);
// 	}
// 	i = -1;	//copy the envp to env_storage
// 	while (envp[++i])
// 	{
// 		env_storage[i] = ft_strdup(envp[i]);
// 		if (env_storage[i] == NULL)
// 		{
// 			free_2d(env_storage);
// 			return (NULL);
// 		}
// 	}
// 	env_storage[i] = NULL;
// 	return (env_storage);
// }

// //function to print environment variable
// void	print_environment(char **env_storage)
// {
// 	int	i;

// 	i = -1;
// 	while (env_storage[++i])
// 		ft_printf("%s\n", env_storage[i]);
// }

// //function to get the environment variable value
// char *get_env_value(char **env_storage, char *value)
// {
// 	int		i;

// 	i = -1;
// 	while (env_storage[++i])
// 	{
// 		if (ft_strncmp(env_storage[i], value, ft_strlen(value)) == 0)
// 		{
// 			value = ft_strchr(env_storage[i], '=') + 1;
// 			return (value);
// 		}
// 	}
// 	return (NULL);
// }

//function make env to link list
t_env_list	*store_env(char **envp)
{
	t_env_list	*env_list;
	t_env_list	*new;
	int			i;

	env_list = NULL;
	i = -1;
	while (envp[++i])
	{
		new = malloc(sizeof(t_env_list));
		if (new == NULL)
		{
			printf("malloc failed\n");
			free_2d(envp);
			exit(EXIT_FAILURE);
		}
		new->env_var = ft_strdup(envp[i]);
		new->next = env_list;
		env_list = new;
	}
	return (env_list);
}

//function to print environment variable
void print_env(t_env_list *env_list)
{
	t_env_list	*tmp;

	tmp = env_list;
	while (tmp)
	{
		ft_printf("%s\n", tmp->env_var);
		tmp = tmp->next;
	}
}

//function to clear env list
void clear_env_list(t_env_list *env_list)
{
	t_env_list	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp->env_var);
		free(tmp);
	}
}

char *get_env_value(t_env_list *env_list, char *name)
{
	t_env_list	*tmp;
	char		*value;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->env_var, name, ft_strlen(name)) == 0)
		{
			value = ft_strchr(tmp->env_var, '=') + 1;
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}