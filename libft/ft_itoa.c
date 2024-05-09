/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:06:43 by welow             #+#    #+#             */
/*   Updated: 2023/10/17 13:47:28 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_len(int n)
{
	size_t	len;

	len = 0;
	if (n < 1)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static long	check_num(long n)
{
	long	nb;

	nb = 1;
	if (n < 0)
		nb *= -n;
	else
		nb *= n;
	return (nb);
}

static char	*n_memory(size_t n)
{
	char	*s;

	s = (char *)malloc(sizeof(char) * (n + 1));
	if (s == NULL)
		return (NULL);
	return (s);
}

char	*ft_itoa(int n)
{
	size_t	nb;
	int		sign;
	int		len;
	char	*str;

	sign = 0;
	if (n < 0)
		sign = 1;
	len = count_len(n);
	str = n_memory(len);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	nb = check_num(n);
	while (len)
	{
		len--;
		str[len] = nb % 10 + '0';
		nb /= 10;
	}
	if (sign != 0)
		*str = '-';
	return (str);
}

// #include <stdio.h>
// int main() {
//     int n = -2147483648;
//     char *result = ft_itoa(n);
// 	printf("Integer: %d\n", n);
//     printf("String: %s\n", result);
// 	free(result);
// }