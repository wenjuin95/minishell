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
void	free_2d(char **str)
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

/*
*	@brief add a content to a garbage collector list (for freeing later)
*	@param content the content that had memory
*	@return the content
*/
void	*to_gc_lst(void *content)
{
	static t_list	*head_lst;
	t_list			**head_ptr;

	head_ptr = &head_lst;
	ft_lstadd_back(head_ptr, ft_lstnew(content));
	return (content);
}

/*
*	@brief free a content from the garbage collector list
*	@param content the content that looks for freeing
*/
void	free_gc(void **content)
{
	static t_list	*head_lst;
	t_list			**head_ptr;
	t_list			*current;
	t_list			*prev;

	prev = NULL;
	if (*content != NULL && content != NULL)
	{
		head_ptr = &head_lst;
		current = *head_ptr;
		while (current->content != *content)
		{
			prev = current;
			current = current->next;
		}
		if (prev == NULL)
			*head_ptr = current->next;
		else
			prev->next = current->next;
		free(current->content);
		free(current);
		*content = NULL;
	}
}

/*
*	@brief free all the contents from the garbage collector list
*/
void	free_gc_lst(void)
{
	static t_list	*head_lst;
	t_list			**head_ptr;

	head_ptr = &head_lst;
	ft_lstclear(head_ptr, free);
}

/*
*	@brief	cleaner function
*	@param	clean_cmd :: flag to clean cmd or env_lst
*	@note	if true, clean cmd
*	@note	if false, clean env_lst and memory
*/
void	ft_clean(t_minishell *m_shell)
{
	free_gc_lst();
	clean_env_lst(m_shell->env_lst);
}
