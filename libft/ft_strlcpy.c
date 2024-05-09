/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:59:48 by welow             #+#    #+#             */
/*   Updated: 2023/10/16 11:59:48 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < size)
		dest[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

// #include <stdio.h>

// int main()
// {
//     char s1[] = "hello";
//     char s2[6];
//     unsigned int length = ft_strlcpy(s2, s1, sizeof(s2));
//     if(length >= sizeof(s2))
//     {
//         printf("error");
//     }
//     else
//     {
//         printf("s1:%s\n", s1);
//         printf("s2:%s\n", s2);
// 	printf("length s2:%d\n", length);
//     }
// }