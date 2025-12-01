/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:08:42 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/12/30 21:42:47 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_addr(unsigned long a)
{
	if (a >= 16)
	{
		ft_put_addr(a / 16);
		ft_put_addr(a % 16);
	}
	else
		ft_putchar2(HEXLOW[a]);
}

static int	ptr_len(unsigned long p)
{
	int	len;

	len = 0;
	if (!p)
		return (1);
	while (p > 0)
	{
		p /= 16;
		len++;
	}
	return (len);
}

int	print_ptr(va_list args, t_flags flags)
{
	unsigned long	p;
	int				len;
	int				p_len;

	len = 0;
	p = (unsigned long)va_arg(args, void *);
	p_len = ptr_len(p);
	if (!p && !flags.precision)
		p_len = 0;
	if (flags.precision < p_len || flags.precision == -1)
		flags.precision = p_len;
	flags.width -= 2;
	len += write(1, "0x", 2 * flags.zero);
	if (!flags.left)
		len += put_padding(flags.width, flags.precision, flags.zero);
	len += write(1, "0x", 2 * !flags.zero);
	len += put_padding(flags.precision, p_len, 1);
	if (p || flags.precision)
		ft_put_addr(p);
	if (flags.left)
		len += put_padding(flags.width, flags.precision, flags.zero);
	return (len + p_len);
}
