/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:30:23 by welow             #+#    #+#             */
/*   Updated: 2024/05/18 19:30:23 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief 	free 2d array
*	@param 	str 2d array
*/
void	free_2d(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

/*
*	@brief 	clean the env link list
*/
void	clean_env_lst(t_env_lst *env_lst)
{
	t_env_lst	*current;
	t_env_lst	*free_node;

	current = env_lst;
	while (current)
	{
		free_node = current;
		current = current->next;
		free(free_node);
	}
	env_lst = NULL;
}

/*
*	@brief	cleaner function
*	@param	clean_cmd flag to clean cmd or env_lst
*	@note	if true, (not yet implemented)
*	@note	if false, clean env_lst and gc and close fds
*/
void	ft_clean(t_minishell *m_shell)
{
	free_gc_lst();
	free_2d(m_shell->env_storage);
	clean_env_lst(m_shell->env_lst);
	close(m_shell->std_fds[STDIN_FILENO]);
	close(m_shell->std_fds[STDOUT_FILENO]);
	close(m_shell->std_fds[STDERR_FILENO]);
}
