/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:10:25 by welow             #+#    #+#             */
/*   Updated: 2024/06/07 16:12:35 by welow            ###   ########.fr       */
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

//function to print all the environment variables with "declare -x"
void print_export(t_env_list *env_list)
{
	t_env_list	*current;

	current = env_list;
	while (current)
	{
		sort_env(current);
		ft_printf("declare -x %s\n", current->env_var);
		current = current->next;
	}
}

void replace_env_var(t_env_list *env_list, char *new_env_var)
{
	t_env_list	*current;
	char		*temp;

	current = env_list;
	while (current)
	{
		if (ft_strncmp(current->env_name, new_env_var, ft_strlen(current->env_name)) == 0)
		{
			temp = current->env_var;
			current->env_var = new_env_var;
			current->env_name = get_env_name(new_env_var);
			current->env_value = get_env_value(new_env_var, current->env_name);
			free(temp);
			return ;
		}
		current = current->next;
	}
}

void add_env_var(t_env_list *env_list, char *new_env_var)
{
	t_env_list	*new;
	t_env_list	*current;

	new = malloc(sizeof(t_env_list));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->env_var = new_env_var;
	new->env_name = get_env_name(new_env_var);
	new->env_value = get_env_value(new->env_var, new->env_name);
	new->next = NULL;
	current = env_list;
	while (current->next)
		current = current->next;
	current->next = new;
}

//function to store the environment variables to export
int update_env_var(t_env_list *env_list, char *name, char *value)
{
	t_env_list	*current;
	char		*new_env_var;
	char		*new_env_value;

	current = env_list;
	if (value == NULL)
		value = "''"; //if no value, assign single quote
	new_env_value = ft_strjoin("=", value);
	// printf("value: %s\n", new_env_value); //debug
	new_env_var = ft_strjoin(name, new_env_value);
	free(new_env_value);
	// printf("new env: %s\n", new_env_var); //debug
	if (new_env_var == NULL)
		return (FALSE);
	if (check_exist_name(current, name) == TRUE)
	{
		if (check_env_value(new_env_var) == TRUE)
			replace_env_var(env_list, new_env_var);
		return (TRUE);
	}
	else
	{
		add_env_var(env_list, new_env_var);
		return (TRUE);
	}
	return (TRUE);
}

// function for export command
int export_option(t_env_list *env_list, char **cmd)
{
	int		i;
	char	*name;
	char	*value;

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
		name = get_env_name(cmd[i]);
		value = get_env_value(cmd[i], name);
		update_env_var(env_list, name, value);
		//print_env(env_list); //not sure export or env
		free(name);
		free(value);
		return (0);
	}
}

