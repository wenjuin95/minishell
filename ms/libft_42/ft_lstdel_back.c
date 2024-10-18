/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:51:50 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/03/21 19:11:03 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_back(t_list **lst, void (*del)(void *))
{
	t_list	*curr;

	if (!lst || !*lst)
		return ;
	if (!(*lst)->next)
	{
		ft_lstdelone(*lst, del);
		*lst = NULL;
	}
	else
	{
		curr = *lst;
		while (curr->next->next)
			curr = curr->next;
		ft_lstdelone(curr->next, del);
		curr->next = NULL;
	}
}
