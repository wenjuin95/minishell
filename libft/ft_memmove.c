/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:55:48 by welow             #+#    #+#             */
/*   Updated: 2023/10/16 11:55:48 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*d;
	const char		*s;
	size_t			i;

	if (dest == 0 && src == 0)
		return (0);
	d = dest;
	s = src;
	i = 0;
	if (d < s)
	{
		while (i < n)
		{
			*(d + i) = *(s + i);
			i++;
		}
	}
	else
	{
		while (n-- > 0)
		{
			*(d + n) = *(s + n);
		}
	}
	return (d);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
//     char s1[] = "oldstring";
//     char s2[] = "newstring";
//     printf("before:\n");
//     printf("s1:%s\n", s1);
//     printf("s2:%s\n\n", s2);
//     memmove(s1, s2, 9);
//     printf("after memmove:\n");
//     printf("s1:%s\n", s1);
//     printf("s2:%s\n", s2);
//     ft_memmove(s1, s2, 9);
//     memmove(s1, s2, 9);
//     printf("after ft_memmove:\n");
//     printf("s1:%s\n", s1);
//     printf("s2:%s\n", s2);
// }
