/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:12:01 by welow             #+#    #+#             */
/*   Updated: 2024/06/13 15:28:08 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// /*
// *	@brief	sort the environment variable in alphabetical order
// *	@param	env_list	pointer to the link list
// */
// void	sort_env(t_env_list *env_list)
// {
// 	t_env_list	*current;
// 	t_env_list	*next;
// 	char		*temp;

// 	current = env_list;
// 	while (current)
// 	{
// 		next = current->next;
// 		while (next)
// 		{
// 			if (ft_strncmp(current->env_var, next->env_var,
// 					ft_strlen(current->env_var)) > 0)
// 			{
// 				temp = current->env_var;
// 				current->env_var = next->env_var;
// 				next->env_var = temp;
// 			}
// 			next = next->next;
// 		}
// 		current = current->next;
// 	}
// }

// /*
// *	@brief	check if the environment variable has value
// *	@param	env_var	environment variable
// *	@return	TRUE if has value, FALSE if not
// */
// int check_env_value(char *env_var)
// {
// 	char	*tmp;

// 	tmp = ft_strchr(env_var, '='); //return the value
// 	if (tmp != NULL && tmp[1] != '\0') //check if has value and next word is not '\0'
// 		return (TRUE);
// 	return (FALSE);
// }

// /*
// *	@brief	check if the environment variable name exist in the link list
// *	@param	env_list	pointer to the link list
// *	@param	env_var		environment variable
// *	@return	TRUE if exist, FALSE if not
// */
// int	check_exist_name(t_env_list *env_list, char *env_var)
// {
// 	t_env_list	*current;

// 	current = env_list;
// 	while (current)
// 	{
// 		if (ft_strncmp(current->env_name, env_var,
// 				ft_strlen(current->env_name)) == 0)
// 			return (TRUE);
// 		current = current->next;
// 	}
// 	return (FALSE);
// }

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