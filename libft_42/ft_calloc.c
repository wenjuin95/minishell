/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:25:55 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/03/13 21:11:10 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*ptr;

	if (nelem != 0 && elsize > UINT_MAX / nelem)
		return (NULL);
	ptr = malloc(nelem * elsize);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, nelem * elsize);
	return (ptr);
}
