/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:32:54 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/10/17 17:37:26 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;
	t_list	*curr;

	i = 0;
	if (lst)
	{
		i++;
		curr = lst;
		while (curr->next)
		{
			i++;
			curr = curr->next;
		}
	}
	return (i);
}
