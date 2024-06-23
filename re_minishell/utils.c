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
void	clean_env_lst(t_env_lst *env_lst)
{
	t_env_lst	*current;
	t_env_lst	*free_node;

	current = env_lst;
	while (current)
	{
		free_node = current; //store the current node
		current = current->next; //move to the next node
		free(free_node); //free the current node
	}
	env_lst = NULL;
}


static void	ft_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

/*
*	@brief 	manage memory function
*	@param	content :: memory store to a linked list
*	@param	clear :: flag to clear the linked list
*	@return 	content that had memory
*	@note	clean == FALSE, add memory to linked list
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
*	@param	clean_cmd :: flag to clean cmd or env_lst
*	@note	if TRUE, clean cmd
*	@note	if FALSE, clean env_lst and memory
*/
void	ft_clean(t_minishell *m_shell, int clean_cmd)
{
	if (clean_cmd == TRUE)
	{
		free_2d(m_shell->split_cmd);
		free(m_shell->cmd); 
	}
	else
	{
		memory_manage(NULL, TRUE);
		clean_env_lst(m_shell->env_lst);
	}
}