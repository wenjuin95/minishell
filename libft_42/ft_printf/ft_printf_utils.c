/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:56:58 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/12/02 16:28:42 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_str_chr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (0);
}

int	ft_is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

size_t	ft_str_len(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

t_flags	new_flag(void)
{
	t_flags	new;

	new.hash = 0;
	new.zero = 0;
	new.left = 0;
	new.space = 0;
	new.plus = 0;
	new.width = 0;
	new.dot = 0;
	new.precision = -1;
	new.spec = 0;
	return (new);
}

int	dec_len(unsigned int u)
{
	int	len;

	len = 0;
	if (!u)
		return (1);
	while (u > 0)
	{
		u /= 10;
		len++;
	}
	return (len);
}

/* to check if flags read properly
#include <stdio.h>

void	print_flags(t_flags flags)
{
	printf("\nhash=%d\n", flags.hash);
	printf("zero=%d\n", flags.zero);
	printf("left=%d\n", flags.left);
	printf("space=%d\n", flags.space);
	printf("plus=%d\n", flags.plus);
	printf("width=%d\n", flags.width);	
	printf("precision=%d\n", flags.precision);
	printf("spec=%c\n", flags.spec);
}*/