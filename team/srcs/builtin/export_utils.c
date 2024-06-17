/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:12:01 by welow             #+#    #+#             */
/*   Updated: 2024/06/17 16:48:38 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief	get the name of the environment variable
*	@param	env_var :: environment variable
*	@return	name of the environment variable
*	@note need to free 
*/
char	*get_name(char *env_var)
{
	int		i;
	char	*name;
	
	if (env_var == NULL) //if env_var is empty, return empty string
	{
		name = ft_strdup("");
		return (name);
	}
	else if (ft_strchr(env_var, '=') == NULL) //if not value return name
	{
		name = ft_strdup(env_var);
		return (name);
	}
	else // if env_var have value then return name
	{
		i = -1;
		while (env_var[++i] != '=')
			;
		name = ft_substr(env_var, 0, i);
		return (name);
	}
}

/*
*	@brief	get the value of the environment variable
*	@param	env_var	:: environment variable
*	@return	value of the environment variable
*	@note need to free
*/
char	*get_value(char *env_var)
{
	int		i;
	char	*value;

	if (env_var == NULL) // if env_var is empty, return empty string
	{
		value = ft_strdup(""); 
		return (value);
	}
	else if (ft_strchr(env_var, '=') == NULL) //if not value return empty string
	{
		value = ft_strdup("");
		return (value);
	}
	else // if env_var have value then return value
	{
		i = -1;
		while (env_var[++i] != '=')
			;
		value = ft_substr(env_var, i + 1, ft_strlen(env_var) - i - 1);
		return (value);
	}
}

/*
*	@brief	replace the environment variable to the link list
*	@param	env_list :: pointer to the link list
*	@param	new_var	:: environment variable
*/
void	replace_env_var(t_env_list *env_list, char *new_var)
{
	t_env_list	*current;
	char		*new_env_name;
	char		*env_name;

	current = env_list;
	while (current)
	{
		new_env_name = get_name(new_var);
		env_name = get_name(current->env_var);
		if (ft_strncmp(new_env_name, env_name, ft_strlen(new_env_name)) == 0)
		{
			free(current->env_var);
			current->env_var = ft_strdup(new_var);
			free(new_var);
			free(new_env_name);
			free(env_name);
			break ;
		}
		free(new_env_name);
		free(env_name);
		current = current->next;
	}
}

/*
*	@brief	add the environment variable to the link list
*	@param	env_list :: pointer to the link list
*	@param	new_var	:: environment variable
*/
void	add_env_var(t_env_list *env_list, char *new_var)
{
	t_env_list	*current;

	current = env_list;
	while (current)
	{
		if (current->next == NULL)
		{
			current->next = malloc(sizeof(t_env_list));
			current->next->env_var = ft_strdup(new_var);
			free(new_var);
			current->next->next = NULL;
			break ;
		}
		current = current->next;
	}
}

/*
*	@brief	join the name and value of the environment variable
*	@param	name :: name of the environment variable
*	@param	value :: value of the environment variable
*	@return	name=value
*/
char	*ft_join_env(char *name, char *value)
{
	char *new_var;

	if (name == NULL) //if name is empty, return empty string
		name = ft_strdup("");
	if (value == NULL) //if value is empty, return empty string
		value = ft_strdup("");
	new_var = ft_strjoin(name, "="); //join name and =
	free(name);
	name = ft_strjoin(new_var, value); //join name= and value
	free(new_var);
	free(value);
	return (name); //return name=value
}