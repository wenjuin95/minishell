/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 22:54:44 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/10/18 21:05:14 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*des_ptr;

	des_ptr = dest;
	if (!dest && !src)
		return (NULL);
	while (n--)
		*(char *)(dest++) = *(char *)(src++);
	return (des_ptr);
}
