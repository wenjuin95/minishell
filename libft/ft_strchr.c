/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:56:52 by welow             #+#    #+#             */
/*   Updated: 2023/10/16 11:56:52 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
	{
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int main ()
// {
//    const char str[] = "geek for geek";
//    const char ch = ' ';
//    char *ret;
//    char *ret2;
//    ret = strchr(str, ch);
//    ret2 = ft_strchr(str, ch);
//    printf("strrchr:|%c| is at |%s|\n", ch, ret);
//    printf("ft_strrchr:|%c| is at |%s|\n", ch, ret2);
//    return(0);
// }
