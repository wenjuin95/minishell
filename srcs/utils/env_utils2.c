/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:17:15 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/09/13 13:13:26 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief goes through the environment variable (which are "name=value" pairs) 
*	@brief , and searches for a string with the requested name and 
*	@brief returns the value
*	@param name the name of the environment variable
*	@param envp the environment variable
*	@note 1. man getenv
*/
char	*ft_getenv(char *name, char *const envp[])
{
	char	**e_ptr;
	int		len;

	if (!envp || !name)
		return (NULL);
	e_ptr = (char **)envp;
	len = ft_strlen(name);
	while (*e_ptr)
	{
		if (ft_strnstr(*e_ptr, name, len) && (*e_ptr)[len] == '=')
			return (*e_ptr + len + 1);
		e_ptr++;
	}
	return (NULL);
}

/*
*	@brief get size of node in the environment list
*	@param env_lst the environment list
*	@return size
*/
static int	ft_env_lstsize(t_env_lst *env_lst)
{
	int			size;
	t_env_lst	*current;

	size = 0;
	current = env_lst;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

/*
*	@brief convert the environment list to an array
*	@param env_lst the environment list
*	@return the environment array
*/
char	**convert_env_lst_to_env_array(t_env_lst *env_lst)
{
	int			list_size;
	int			i;
	char		**env_array;
	t_env_lst	*current;

	list_size = ft_env_lstsize(env_lst);
	env_array = calloc(list_size + 1, sizeof(char *));
	if (!env_array)
		return (NULL);
	current = env_lst;
	i = 0;
	while (current)
	{
		env_array[i] = to_gc_lst(ft_strjoin(current->name, "="));
		env_array[i] = to_gc_lst(ft_strjoin(env_array[i], current->value));
		current = current->next;
		i++;
	}
	return (to_gc_lst(env_array));
}
