/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:38:58 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/10/18 14:20:49 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*curr;

	if (lst)
	{
		curr = lst;
		while (curr->next)
		{
			curr = curr->next;
		}
		return (curr);
	}
	return (NULL);
}
