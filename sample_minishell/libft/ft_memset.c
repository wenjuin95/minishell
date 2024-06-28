/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 01:47:32 by ychng             #+#    #+#             */
/*   Updated: 2024/03/05 01:56:40 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	unsigned char	*destination;

	if (!dest)
		return (NULL);
	destination = (unsigned char *)dest;
	while (n--)
		*destination++ = (unsigned char)c;
	return (dest);
}
