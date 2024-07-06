/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:55:44 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/26 14:55:48 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief check name in env_lst
*	@param name name to be checked
*	@return TRUE if the name exist, FALSE if not
*/
int	check_name_exist(char *name, t_minishell *m_shell)
{
	t_env_lst	*current;

	current = m_shell->env_lst;
	while (current)
	{
		if (ft_strncmp(current->name, name, ft_strlen(name)) == 0)
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}

/*
*	@brief create new env_var
*	@param name :: name of the env_var
*	@param value :: value of the env_var
*	@return new env_var
*	@note if value is NULL, then return only name
*/
t_env_lst	*ft_env_new(char *name, char *value)
{
	t_env_lst	*new;

	new = ft_calloc(1, sizeof(t_env_lst));
	if (new == NULL)
		return (NULL);
	new->name = to_gc_lst(ft_strdup(name));
	if (value)
		new->value = to_gc_lst(ft_strdup(value));
	new->next = NULL;
	return (new);
}

/*
*	@brief add new env_var to the env_lst
*	@param new :: new env_var to add
*/
void	ft_env_add_back(t_minishell *m_shell, t_env_lst *new)
{
	t_env_lst	*current;

	if (m_shell->env_lst == NULL)
	{
		m_shell->env_lst = new;
		return ;
	}
	current = m_shell->env_lst;
	while (current != NULL && current->next != NULL)
		current = current->next;
	current->next = new;
}

/*
*	@brief add or replace env_var
*	@param name :: name of the env_var
*	@param value :: value of the env_var
*	@param create :: flag for handle add or replace
*	@note if create is true, add
*	@note if create is false, replace
*/
void	update_env(char *name, char *value, int add, t_minishell *m_shell)
{
	t_env_lst	*current;

	current = m_shell->env_lst;
	while (current)
	{
		if (ft_strncmp(name, current->name, ft_strlen(name)) == 0) //found the env_var just update the value
		{
			if (value)
				current->value = to_gc_lst(ft_strdup(value));
			return ;
		}
		current = current->next;
	}
	if (add == true)
		ft_env_add_back(m_shell, ft_env_new(name, value));
}
