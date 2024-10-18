/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:14:43 by welow             #+#    #+#             */
/*   Updated: 2024/08/17 00:57:23 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
*	@brief free all the contents from the garbage collector list
*/
void	free_gc_lst(void)
{
	static t_list	*head_lst;
	t_list			**head_ptr;

	head_ptr = &head_lst;
	ft_lstclear(head_ptr, free);
}
