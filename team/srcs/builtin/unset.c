/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:07:35 by welow             #+#    #+#             */
/*   Updated: 2024/05/30 18:07:35 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	TODO:
*	1. unset
*	2. unset [any argument]
*/

/*
*	@brief 	remove the environment variable
*/
static void	remove_env_var(t_minishell *m_shell, char *name)
{
	t_env_lst	*current;
	t_env_lst	*prev;

	prev = NULL;
	current = m_shell->env_lst;
	while (current)
	{
		if (ft_strncmp(name, current->name, ft_strlen(name)) == 0) //found the name
		{
			if (prev != NULL) //current node is not the first node
				prev->next = current->next;  //link the previous node to the next node
			else //current node is the first node
				m_shell->env_lst = current->next; //move the head to the next node
			free(current); //free current node
			return ;//return to the main function
		}
		prev = current;
		current = current->next;
	}
}

int	unset_option(t_minishell *m_shell, char **cmd)
{
	int	i;

	i = 1;
	if (cmd[i] == NULL)
		return (0);
	while (cmd[i])
	{
		remove_env_var(m_shell, to_gc_lst(get_name(cmd[i])));
		i++;
	}
	return (0);
}
