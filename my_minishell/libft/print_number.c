/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:40:16 by welow             #+#    #+#             */
/*   Updated: 2024/01/28 23:08:12 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	int		count;
	long	nb;

	count = 0;
	nb = n;
	if (nb < 0)
	{
		count += ft_putchar('-');
		nb *= -1;
	}
	if (nb >= 10)
	{
		count += ft_putnbr(nb / 10);
		nb %= 10;
	}
	count += ft_putchar(nb + '0');
	return (count);
}

int	ft_putnbr_unsigned(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb >= 10)
	{
		count += ft_putnbr_unsigned(nb / 10);
		nb %= 10;
	}
	count += ft_putchar(nb + '0');
	return (count);
}

int	ft_puthexa_upper(unsigned int nb)
{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789ABCDEF";
	if (nb >= 16)
	{
		count += ft_puthexa_upper(nb / 16);
		nb %= 16;
	}
	count += write(1, &base[nb], 1);
	return (count);
}

int	ft_puthexa_lower(unsigned int nb)
{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789abcdef";
	if (nb >= 16)
	{
		count += ft_puthexa_lower(nb / 16);
		nb %= 16;
	}
	count += write(1, &base[nb], 1);
	return (count);
}
