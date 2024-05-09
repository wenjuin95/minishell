/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:59:43 by welow             #+#    #+#             */
/*   Updated: 2023/10/16 11:59:43 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	d_len;
	size_t	t_len;
	size_t	i;

	if (size == 0 && (src == 0 || dest == 0))
		return (0);
	d_len = ft_strlen(dest);
	if (size <= d_len)
		return (size + ft_strlen(src));
	else
		t_len = d_len + ft_strlen(src);
	i = 0;
	while (src[i] && d_len < size - 1)
	{
		dest[d_len] = src[i];
		d_len++;
		i++;
	}
	dest[d_len] = '\0';
	return (t_len);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
    char s1[20] = "hello ";
    char s2[] = "world";
    unsigned int length = ft_strlcat(s1, s2, sizeof(s1));
    printf("s1:%s\n", s1);
    printf("total length of s1:%d\n", length);
}*/
