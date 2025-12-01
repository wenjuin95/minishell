/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:06:52 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/03/21 16:19:21 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*curr;

	if (!del || !lst)
		return ;
	else
	{
		curr = *lst;
		while (curr)
		{
			temp = curr->next;
			ft_lstdelone(curr, del);
			curr = temp;
		}
		*lst = NULL;
	}
}
