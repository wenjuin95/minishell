/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:55:33 by welow             #+#    #+#             */
/*   Updated: 2023/10/16 11:55:33 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		if (*(((unsigned char *)s) + i) == (unsigned char)c)
			return (((unsigned char *)s) + i);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
//     char str[] = "geek for geeks";
//     char c = ' ';
//     char *ret = memchr(str, c, sizeof(str));
// 	char *ret2 = ft_memchr(str, c, sizeof(str));
//     printf("memchr: string after |%c| is at |%s|\n", c, ret);
// 	printf("ft_memchr: string after |%c| is at |%s|\n", c, ret2);
// }
