/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:10:25 by welow             #+#    #+#             */
/*   Updated: 2024/06/21 23:16:32 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*
*	@brief	sort the environment variable in alphabetical order
*	@param	env_list	pointer to the link list
*/
void	sort_env(t_env_list *env_list)
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

/*
*	@brief	print the environment variable with "declare -x"
*	@param	env_list pointer to the link list
*/
void	print_export(t_env_list *env_list)
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

/*
*	@brief	check if the name of the environment variable exist
*	@param	env_list	pointer to the link list
*	@param	env_var		environment variable
*	@return	TRUE if exist, FALSE if not exist
*/
int	check_name_exist(t_env_list *env_list, char *env_var)
{
	char 	*name;
	
	name = get_name(env_var);
	while (env_list)
	{
		if (ft_strncmp(name, env_list->env_var, ft_strlen(name)) == 0)
		{
			free(name);
			return (TRUE);
		}
		env_list = env_list->next;
	}
	free(name);
	return (FALSE);
}

/*
*	@brief	check if the environment variable exist or not and update it
*	@param	env_list	pointer to the link list
*	@param	env_var		environment variable
*/
void	check_and_update_env(t_env_list *env_list, char *env_var)
{
	char *name;
	char *value;
	char *new_var;

	if (check_name_exist(env_list, env_var) == TRUE)
	{
		name = get_name(env_var);
		value = get_value(env_var);
		new_var = ft_join_env(name, value);	
		replace_env_var(env_list, new_var);
	}
	else
	{
		name = get_name(env_var);
		value = get_value(env_var);
		new_var = ft_join_env(name, value);
		add_env_var(env_list, new_var);
	}
}

/*
*	@brief	handle export command
*	@param	env_list	pointer to the link list
*	@param	cmd			argument
*	@return	0 if success, 1 if error
*/
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
		else
		{
			check_and_update_env(env_list, cmd[i]);
			return (0);
		}	
	}
	return (0);
}