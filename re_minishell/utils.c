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
*	@brief 	clear the env list
*/
void	clean_env_lst(void)
{
	t_env_lst	*current;
	t_env_lst	*free_node;

	current = m_shell.env_lst;
	while (current)
	{
		free_node = current; //store the current node
		current = current->next; //move to the next node
		free(free_node); //free the current node
	}
	m_shell.env_lst = NULL;
}


static void	ft_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

/*
*	@brief 	manage memory allocation
*	@param	content :: content to be store into linked list
*	@param	clear :: flag to clear the linked list
*	@return 	content
*	@note	clean == FALSE, add the content to make a linked list
*	@note	clean == TRUE, clear the whole linked list
*/
void	*memory_manage(void *content, int clean)
{
	static t_list	*head_lst; 

	if (clean == TRUE)
	{
		ft_lstclear(&head_lst, ft_free);
		return (NULL);
	}
	else
	{
		ft_lstadd_back(&head_lst, ft_lstnew(content));
		return (content);
	}
}

/*
*	@brief	cleaner function
*	@note	clean memory_manage and env_lst
*/
void	ft_clean(void)
{
	memory_manage(NULL, TRUE);
	clean_env_lst();
}