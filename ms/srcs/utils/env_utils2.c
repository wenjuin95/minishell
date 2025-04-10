/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:17:15 by tkok-kea          #+#    #+#             */
/*   Updated: 2025/03/19 16:24:02 by welow            ###   ########.fr       */
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

void	update_path(t_minishell *m_shell, char *locate)
{
	t_env_lst	*current;
	char		*new_value;
	int			new_value_len;

	current = m_shell->env_lst;
	while (current)
	{
		if (ft_strncmp("PATH", current->name, ft_strlen("PATH")) == 0)
		{
			new_value_len = ft_strlen(current->value) + ft_strlen(locate) + 2;
			new_value = malloc(new_value_len);
			if (new_value == NULL)
				return;
			ft_strlcpy(new_value, current->value, new_value_len);
			ft_strlcat(new_value, ":", new_value_len);
			ft_strlcat(new_value, locate, new_value_len);
			free(current->value);
			current->value = new_value;
			return;
		}
		current = current->next;
	}
}