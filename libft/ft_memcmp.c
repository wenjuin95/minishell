/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:55:39 by welow             #+#    #+#             */
/*   Updated: 2023/10/16 11:55:39 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
*	@brief	compare two memory blocks
*	@param	s1 :: the first memory block
*	@param	s2 :: the second memory block
*	@param	n :: the size of the memory block
*	@return	0 if the memory blocks are equal,
			otherwise the difference between the first different byte
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char		*p1;
	const unsigned char		*p2;
	size_t					i;

	p1 = s1;
	p2 = s2;
	i = 0;
	while (i < n)
	{
		if (*(p1 + i) != *(p2 + i))
		{
			return (*(p1 + i) - *(p2 + i));
		}
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int main ()
// {
//    char str1[] = "ABCDEf";
//    char str2[] = "ABCDEF";
//    int ret = memcmp(str1, str2, 0);
//    int ret2 = ft_memcmp(str1, str2, 0);

//    printf("memcmp:%d\n", ret);
//    printf("ft_memcmp:%d\n", ret2);
// }
