/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 22:32:01 by welow             #+#    #+#             */
/*   Updated: 2024/06/29 17:52:21 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief check name in env_lst
*	@param name name to be checked
*	@return true if the name exist, false if not
*/
bool	check_name_exist(char *name, t_minishell *m_shell)
{
	t_env_lst	*current;

	current = m_shell->env_lst;
	while (current)
	{
		if (ft_strncmp(current->name, name, ft_strlen(name)) == 0)
			return (true);
		current = current->next;
	}
	return (false);
}

/*
*	@brief create new env_var
*	@param name :: name of the env_var (store to gc for modifcation)
*	@param value :: value of the env_var (store to gc for modifcation)
*	@return new env_var
*	@note if value is NULL, then return only name
*/
t_env_lst	*ft_env_new(char *name, char *value)
{
	t_env_lst	*new;

	new = ft_calloc(1, sizeof(t_env_lst));
	if (new == NULL)
		return (NULL);
	new->name = to_gc_lst(ft_strdup(name), true);//debug
	if (value)
		new->value = to_gc_lst(ft_strdup(value), true);//debug
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
*	@brief add or replace env_var in env_lst
*	@param name :: name of the env_var
*	@param value :: value of the env_var (store to gc for modifcation)
*	@param create :: flag for handle add or replace
*	@note if create is true, add
*	@note if create is false, replace
*/
void	update_env(char *name, char *value, bool add, t_minishell *m_shell)
{
	t_env_lst	*current;

	current = m_shell->env_lst;
	while (current)
	{
		if (ft_strncmp(name, current->name, ft_strlen(name)) == 0) //found the env_var just update the value
		{
			if (value)
				current->value = to_gc_lst(ft_strdup(value), false); //debug
			return ;
		}
		current = current->next;
	}
	if (add == true)
		ft_env_add_back(m_shell, ft_env_new(name, value));
}
