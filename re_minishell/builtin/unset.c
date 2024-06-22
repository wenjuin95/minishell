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
*	@brief	remove the environment variable
*	@param	env_list :: pointer to the link list
*	@param	cmd :: name want to remove
*/
void remove_env_var(t_env_list *env_list, char *cmd)
{
	t_env_list	*current;
	t_env_list	*prev;

	current = env_list;
	prev = NULL;
	while(current)
	{
		if (ft_strncmp(cmd, current->env_var, ft_strlen(cmd)) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				env_list = current->next;
			free(current->env_var);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

/*
*	@brief	handle unset command
*	@param	env_list :: pointer to the link list
*	@param	cmd :: name want to remove
*	@return	0 if success, 1 if fail
*/
int	unset_option(t_env_list *env_list, char **cmd)
{
	int	i;

	i = 1;
	if (cmd[i] != NULL)
	{
		if (check_name_exist(env_list,cmd[i]) == TRUE)
		{
			remove_env_var(env_list, cmd[i]);
			return (0);
		}
	}
	return (1);
}