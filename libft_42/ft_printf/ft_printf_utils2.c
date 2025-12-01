/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:05:35 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/12/02 16:22:41 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ft_putchar with return value */
int	ft_putchar2(char c)
{
	return (write(1, &c, 1));
}

/* ft_putstr with return */
int	ft_putstr2(char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (0);
	while (*s)
	{
		len += write(1, s, 1);
		s++;
	}
	return (len);
}

/* ft_putstr with precision */
int	ft_putstr_prec(char *s, int preci)
{
	int	i;

	i = 0;
	if (preci == -1)
		return (ft_putstr2(s));
	while (s[i] && preci-- > 0)
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	put_padding(int start, int end, int iszero)
{
	int	len;

	len = 0;
	while (start > end)
	{
		if (iszero)
			len += ft_putchar2('0');
		else
			len += ft_putchar2(' ');
		start--;
	}
	return (len);
}
