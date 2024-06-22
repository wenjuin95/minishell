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
*	@param 	str :: 2d array
*/
void free_2d(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

/*
*	@brief	use flag to clean up the minishell struct
*	@param	m_shell :: minishell struct
*	@param	c_cmd :: flag for control clean cmd
*	@param	c_split :: flag for control clean split cmd
*	@param	c_env :: flag for control clean env list
*	@note	custom your own clean up and flag
*/
void	ft_clean(t_minishell m_shell, int c_split, int c_env)
{
	if (m_shell.cmd != NULL)
		free(m_shell.cmd);
	else
		return ;
	if (m_shell.split_cmd != NULL && c_split == TRUE)
		free_2d(m_shell.split_cmd);

	if (m_shell.env_list != NULL && c_env == TRUE)
		clear_env_list(m_shell.env_list);
}

static void	ft_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

/*
*	@brief 	manage memory allocation
*	@param	ptr :: pointer to the memory
*	@param	clear :: flag to clear the memory
*	@return 	pointer to the memory
*	@note	if not clean, add the ptr to the list
*	@note	if clean, clear the whole list
*/
void	memory_manage(void *ptr, int clean)
{
	t_list *ptr_lst;

	if (clean == TRUE)
	{
		ft_lstclear(&ptr_lst, ft_free);
		return (NULL);
	}
	else
	{
		ft_lstadd_back(&ptr_lst, ft_lstnew(ptr));
		return (ptr);
	}
}
