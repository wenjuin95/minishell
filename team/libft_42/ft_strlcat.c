/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:09:21 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/11/02 17:07:02 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	if (!dst && !size)
		return (0);
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = dst_len;
	j = 0;
	if (i < (size - 1) && size > 0)
	{
		while (src[j] && i < (size - 1))
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = 0;
	}
	if (dst_len > size)
		dst_len = size;
	return (dst_len + src_len);
}
