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

/*
 *	TODO:
 *	1. env
 *	2. env [any argument]
 */

/*
*	@brief get name from the env_var
*	@param env_var :: env variable
*	@return name of the env_var
*	@note if no '=' found, return the whole string
*	@note if found '=' then return the string before it
*	@note memory need to be free
*/
char	*get_name(char *env_var)
{
	int	i;

	i = -1;
	while (env_var[++i])
	{
		if (env_var[i] == '=') //if found '=' then return the string before it
			return (memory_manage(ft_substr(env_var, 0, i), FALSE)); //return the string before '='
		i++;
	}
	return (ft_strdup(env_var)); //if no '=' found, return the whole string
}

/*
*	@brief get value from the env_var
*	@param env_var :: env variable
*	@return value of the env_var
*	@note if no '=' found, return NULL
*	@note if found '=' then return the string after it
*/
char *get_value(char *env_var)
{
	int	i;

	i = -1;
	while (env_var[++i])
	{
		if (env_var[i] == '=')
		{
			i++;
			return (memory_manage(ft_substr(env_var, i, ft_strlen(env_var) - i),
				FALSE));
		}
	}
	return (NULL);
}

void	ft_env_add_back(t_env_lst *new)
{
	t_env_lst	*current;

	if (m_shell.env_lst == NULL)
	{
		m_shell.env_lst = new;
		return ;
	}
	current = m_shell.env_lst;
	while (current != NULL && current->next != NULL)
		current = current->next;
	current->next = new;
}

/*
*	@brief update or create env_lst
*	@param name :: name of the env_var
*	@param value :: value of the env_var
*	@param create :: flag for create new_env_var
*	@note if create is TRUE, then create new env_var
*	@note if create is FALSE, then update the env_var
*/
void	update_env_lst(char *name, char *value, int create)
{
	t_env_lst	*current;

	current = m_shell.env_lst;
	while (current)
	{
		if (ft_strncmp(name, current->env_name, ft_strlen(name)) == 0)
		{
			if (value != NULL)
				current->env_value = memory_manage(ft_strdup(value), FALSE);
			return ;
		}
		current = current->next;
	}
	if (create == TRUE)
		ft_env_add_back(ft_env_new(name, value));
}

void	store_env(void)
{
	int		i;
	char	**env;
	char	*env_name;
	char	*env_value;

	env = m_shell.env_storage;
	if (env == NULL)
		return ;
	i = -1;
	while (env[++i])
	{
		env_name = get_name(env[i]);
		env_value = get_value(env[i]);
		update_env_lst(env_name, env_value, TRUE);
	}
}	

