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

static void	remove_env_var(char *name)
{
	t_env_lst	*current;
	t_env_lst	*prev;

	prev = NULL;
	current = m_shell.env_lst;
	while (current)
	{
		if (ft_strncmp(name, current->name, ft_strlen(name)) == 0) //found the name
		{
			if (prev != NULL) //if the node is not the first node
				prev->next = current->next; 
			else
				m_shell.env_lst = current->next;
			free(current); //free the node
			return ; //return to the main function
		}
		prev = current;
		current = current->next;
	}
}

int	unset_option(char **cmd)
{
	int	i;

	i = 1;
	if (cmd[i] == NULL)
		return (0);
	while (cmd[i])
	{
		if (check_alphanum(cmd[i]) == FALSE)
		{
			printf("minishell: unset: `%s': not a valid identifier\n", cmd[i]);
			return (1);
		}
		else
			remove_env_var(memory_manage(get_name(cmd[i]), FALSE));
		i++;
	}
	return (0);
}
