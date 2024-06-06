/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:10:25 by welow             #+#    #+#             */
/*   Updated: 2024/06/06 13:20:36 by welow            ###   ########.fr       */
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

// void	sort_env(char **env_storage)
// {
// 	int		i;
// 	int		j;
// 	int		len;
// 	char	*temp;

// 	i = 0;
// 	len = ft_2d_len(env_storage);
// 	while (i < len)
// 	{
// 		j = i + 1;
// 		while (j < len)
// 		{
// 			if (ft_strncmp(env_storage[i], env_storage[j],
// 					ft_strlen(env_storage[i])) > 0)
// 			{
// 				temp = env_storage[i];
// 				env_storage[i] = env_storage[j];
// 				env_storage[j] = temp;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// //function store the environment variables to export
// char	**store_to_export(char **env_storage)
// {
// 	int	i;

// 	sort_env(env_storage);
// 	i = 0;
// 	while (env_storage[i])
// 	{
// 		env_storage[i] = ft_strjoin("declare -x ", env_storage[i]);
// 		i++;
// 	}
// 	return (env_storage);
// }

// //function either store at env_storage or export storage
// char	**store_option(char **env_storage, char **cmd)
// {
// 	int		i;
// 	char	**tmp_env;

// 	i = 1;
// 	while (cmd[i] != NULL)
// 	{
// 		if (ft_strchr(cmd[i], '=') != NULL) //if the variable had value
// 		{
// 			tmp_env = ft_split(cmd[i], '=');
// 			env_storage = add_or_replace_env(env_storage, tmp_env[0],
// 					tmp_env[1]);
// 			free_2d(tmp_env);
// 		}
// 		else //if the variable no value
// 		{
// 			env_storage = add_or_replace_env(env_storage, cmd[i], "");
// 			env_storage = store_to_export(env_storage);
// 		}
// 		i++;
// 	}
// 	return (env_storage);
// }

// //function for export command
// char **export_option(char **env_storage, char **cmd)
// {
// 	int		i;

// 	i = 1;
// 	if (cmd[i] == NULL) //env list + [declare -x] to export list
// 		return (store_to_export(env_storage));
// 	else //add the new env to the export list
// 	{
// 		if (ft_isalpha(cmd[i][0]) == 0)
// 		{
// 			printf("export: `%s': not a valid identifier\n", cmd[i]);
// 			return (env_storage);
// 		}
// 		env_storage = store_option(env_storage, cmd);
// 		return (env_storage);
// 	}
// }

//function to sort link list
void sort_env(t_env_list *env_list)
{
	t_env_list	*current;
	t_env_list	*next;
	char		*temp;

	current = env_list;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (ft_strncmp(current->env_var, next->env_var,
					ft_strlen(current->env_var)) > 0)
			{
				temp = current->env_var;
				current->env_var = next->env_var;
				next->env_var = temp;
			}
			next = next->next;
		}
		current = current->next;
	}
}

//function to print all the environment variables with "declare -x"
void print_export(t_env_list *env_list)
{
	t_env_list	*current;

	current = env_list;
	while (current)
	{
		sort_env(current);
		printf("declare -x %s\n", current->env_var);
		current = current->next;
	}
}

//REPLACE :: check env variable had value
int check_env_value(char *env_var)
{
	if (ft_strchr(env_var, '=') != NULL)
		return (TRUE);
	return (FALSE);
}

//REPLACE :: check the name exist in env list
int check_exist_name(t_env_list *env_list, char *env_var)
{
	t_env_list	*current;

	current = env_list;
	while (current)
	{
		if (ft_strncmp(current->env_name, env_var, ft_strlen(current->env_name)) == 0)
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}

//function to store the environment variables to export
t_env_list	add_replace_env_var(t_env_list *env_list, char *env_var)
{
	t_env_list	*current;
	t_env_list	*new;
	int			i;
	//TODO :: check and add the new env to the export list
	if (check_env_value(env_var) == TRUE)
	{
		new = malloc(sizeof(t_env_list));
		if (new == NULL)
			exit(EXIT_FAILURE);
		new->env_var = ft_strdup(env_var);
		new->env_name = get_env_name(env_var);
		new->env_value = get_env_value(new->env_var, new->env_name);
		new->next = env_list;
		env_list = new;
	}
	else
	{
		if (check_exist_name(env_list, env_var) == FALSE)
		{
			unset_var(env_list, env_var);
			new = malloc(sizeof(t_env_list));
			if (new == NULL)
				exit(EXIT_FAILURE);
			new->env_var = ft_strdup(env_var);
			new->env_name = get_env_name(env_var);
			new->env_value = get_env_value(new->env_var, new->env_name);
			new->next = env_list;
			env_list = new;
		}
		else
		{
			new = malloc(sizeof(t_env_list));
			if (new == NULL)
				exit(EXIT_FAILURE);
			new->env_var = ft_strdup(env_var);
			new->env_name = get_env_name(env_var);
			new->env_value = get_env_value(new->env_var, new->env_name);
			new->next = env_list;
			env_list = new;
		}
	}
}

// function for export command
int export_option(t_env_list *env_list, char **cmd)
{
	int		i;

	i = 1;
	if (cmd[i] == NULL)
	{
		print_export(env_list);
		return (0);
	}
	else
	{
		if (ft_isalpha(cmd[i][0]) == 0)
		{
			printf("export: `%s': not a valid identifier\n", cmd[i]);
			return (1);
		}
		//TODO :: store the new env to the export list
		env_list->env_name = get_env_name(cmd[i]);
		env_list->env_value = get_env_value(cmd[i], env_list->env_name);
		add_replace_env_var(env_list, env_list->env_name, env_list->env_value);
		return (0);
	}
}

