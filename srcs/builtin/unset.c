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
*	@param	m_shell get the env_lst from m_shell
*	@param	name :: name of the env_var to remove
*/
void	remove_env_var(t_minishell *m_shell, char *name)
{
	t_env_lst	*current;
	t_env_lst	*prev;

	prev = NULL;
	current = m_shell->env_lst;
	while (current)
	{
		if (ft_strncmp(name, current->name, ft_strlen(name)) == 0)
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				m_shell->env_lst = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

/*
*	@brief	handle unset command
*	@param	cmd argument
*	@param	m_shell get the exit code and enc link list from m_shell
*	@return	0 if success remove
*/
int	unset_option(char **cmd, t_minishell *m_shell)
{
	int	i;

	i = 1;
	m_shell->exit_code = EXIT_SUCCESS;
	if (cmd[i] == NULL)
		return (m_shell->exit_code);
	while (cmd[i])
	{
		remove_env_var(m_shell, get_name(cmd[i]));
		i++;
	}
	return (m_shell->exit_code);
}
