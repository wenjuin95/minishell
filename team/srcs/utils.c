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
*	@note check == 0, get_name
*	@note check == 1, get_value
*	@note check == 2, update_env
*	@note check == 3, env_new
*	@note check == 4, remove_env
*/
void	*to_gc_lst(void *content, int check)
{
	static t_list	*head_lst;
	t_list			**head_ptr;

	head_ptr = &head_lst;
	ft_lstadd_back(head_ptr, ft_lstnew(content));
	//debug
	if(check == 0)
		printf("\033[0;44mget_name: [ %s ]\033[0m\n", (char *)content);
	else if (check == 1)
		printf("\033[0;44mget_value: [ %s ]\033[0m\n", (char *)content);
	else if (check == 2)
		printf("\033[0;42mupdate_env: [ %s ]\033[0m\n", (char *)content);
	else if (check == 3)
		printf("\033[0;43menv_new: [ %s ]\033[0m\n", (char *)content);
	else if (check == 4)
		printf("\033[0;41mremove_env: [ %s ]\033[0m\n", (char *)content);
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
