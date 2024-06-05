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

//function break the env variable to name and value
// t_env_list *ft_split_env(char *env_var)
// {

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
			exit(EXIT_FAILURE);
		new->env_var = ft_strdup(envp[i]);
		new->env_name = get_env_name(envp[i]);
		new->env_value = get_env_value(new->env_var, new->env_name);
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
		ft_printf("name: %s\n", tmp->env_name); //debug
		ft_printf("value: %s\n\n", tmp->env_value); //debug
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

//function for get the value of the env variable
char *get_env_value(char *env_var, char *name)
{
	int		i;
	char	*value;

	i = ft_strlen(name) + 1;
	value = ft_strdup(env_var + i);
	if (value == NULL)
		exit(EXIT_FAILURE);
	return (value);
}

//function get env name
char	*get_env_name(char *env_var)
{
	char *name;
	int i;

	i = 0;
	while (env_var[i] != '=')
		i++;
	name = ft_substr(env_var, 0, i);
	return (name);
}
