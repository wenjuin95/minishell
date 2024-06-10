/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:20:36 by welow             #+#    #+#             */
/*   Updated: 2024/06/09 14:31:23 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
*	@brief	iterate the list and apply function for each node
*			if the function fails, free the list
*	@param	lst :: the node to start iterating
*	@param	f :: the function to apply
*	@param	del :: the function to delete the content of a node
*	@return	the new list
*	@note	need to free the returned pointer
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*node;

	if (lst == NULL || f == NULL || del == NULL)
		return (0);
	new = ft_lstnew(f(lst->content));
	if (new == NULL)
		return (0);
	node = new;
	lst = lst->next;
	while (lst)
	{
		new->next = ft_lstnew(f(lst->content));
		if ((new->next) == NULL)
		{
			ft_lstclear(&node, del);
			return (0);
		}
		new = new->next;
		lst = lst->next;
	}
	new->next = NULL;
	return (node);
}
