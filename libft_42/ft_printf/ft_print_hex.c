/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:18:14 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/12/30 21:42:43 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*xtoa(unsigned int x, int len, int spec)
{
	char	*nbr;
	char	*hex_symbol;

	nbr = (char *)malloc(sizeof(*nbr) * (len + 1));
	if (!nbr)
		return (NULL);
	if (spec == 'X')
		hex_symbol = HEXUP;
	else
		hex_symbol = HEXLOW;
	nbr[len] = '\0';
	len--;
	while (len)
	{
		nbr[len] = hex_symbol[x % 16];
		x /= 16;
		len--;
	}
	nbr[len] = hex_symbol[x % 16];
	return (nbr);
}

static int	hex_len(unsigned int x)
{
	int	len;

	len = 0;
	if (!x)
		return (1);
	while (x > 0)
	{
		x /= 16;
		len++;
	}
	return (len);
}

int	put_pre(char spec)
{
	if (spec == 'X')
		ft_putstr2("0X");
	else
		ft_putstr2("0x");
	return (2);
}

int	put_hex(char *nbr, t_flags fl, int x_len)
{
	int	len;

	len = 0;
	if (fl.hash && *nbr != '0')
		len += put_pre(fl.spec);
	if (!fl.left && fl.zero)
		len += put_padding(fl.width, fl.precision, fl.zero);
	len += put_padding(fl.precision, x_len, 1);
	if (*nbr != '0' || fl.precision)
		len += ft_putstr2(nbr);
	if (fl.left)
		len += put_padding(fl.width, fl.precision, fl.zero);
	return (len);
}

int	print_hex(va_list args, t_flags fl)
{
	unsigned int	x;
	int				len;
	int				x_len;
	char			*nbr;

	len = 0;
	x = va_arg(args, unsigned int);
	x_len = hex_len(x);
	nbr = xtoa(x, x_len, fl.spec);
	if (!nbr)
		return (0);
	if (!x && !fl.precision)
		x_len = 0;
	if (fl.precision != -1)
		fl.zero = 0;
	if (fl.precision < x_len || fl.precision == -1)
		fl.precision = x_len;
	if (fl.hash && x != 0)
		fl.width -= 2;
	if (!fl.left && !fl.zero)
		len += put_padding(fl.width, fl.precision, 0);
	len += put_hex(nbr, fl, x_len);
	free(nbr);
	return (len);
}
