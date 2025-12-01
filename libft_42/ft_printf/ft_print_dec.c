/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:37:34 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/12/30 21:42:37 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*utoa(long u)
{
	char	*nbr;
	int		len;

	len = dec_len(u);
	nbr = (char *)malloc(sizeof(*nbr) * (len + 1));
	if (!nbr)
		return (NULL);
	nbr[len] = '\0';
	len--;
	while (len)
	{
		nbr[len] = (u % 10) + '0';
		u /= 10;
		len--;
	}
	nbr[len] = u + '0';
	return (nbr);
}

int	put_symbols(int space, int plus, int isneg)
{
	int	len;

	len = 0;
	if (space && !plus && !isneg)
		len += ft_putchar2(' ');
	else if (plus && !isneg)
		len += ft_putchar2('+');
	if (isneg)
		len += ft_putchar2('-');
	return (len);
}

int	ft_put_nbr(char *nbr, int isneg, t_flags fl)
{
	int	len;
	int	s_len;

	len = 0;
	s_len = ft_str_len(nbr);
	if (*nbr == '0' && !fl.precision)
		s_len = 0;
	if (fl.precision < s_len || fl.precision == -1)
		fl.precision = s_len;
	if (isneg || fl.space || fl.plus)
		fl.width -= 1;
	if (!fl.left && !fl.zero)
		len += put_padding(fl.width, fl.precision, fl.zero);
	len += put_symbols(fl.space, fl.plus, isneg);
	if (!fl.left && fl.zero)
		len += put_padding(fl.width, fl.precision, fl.zero);
	len += put_padding(fl.precision, s_len, 1);
	if (*nbr != '0' || fl.precision)
		len += ft_putstr2(nbr);
	if (fl.left)
		len += put_padding(fl.width, fl.precision, fl.zero);
	return (len);
}

int	print_dec(va_list args, t_flags fl)
{
	int		i;
	long	u;
	int		len;
	char	*nbr;
	int		isneg;

	i = va_arg(args, int);
	len = 0;
	isneg = 0;
	u = i;
	if (i < 0)
	{
		u *= -1;
		isneg = 1;
	}
	nbr = utoa(u);
	if (!nbr)
		return (0);
	if (fl.precision != -1)
		fl.zero = 0;
	len += ft_put_nbr(nbr, isneg, fl);
	free(nbr);
	return (len);
}

int	print_u(va_list args, t_flags fl)
{
	unsigned int	u;
	int				len;
	char			*nbr;

	u = va_arg(args, unsigned int);
	len = 0;
	nbr = utoa(u);
	if (!nbr)
		return (0);
	fl.plus = 0;
	fl.space = 0;
	if (fl.precision != -1)
		fl.zero = 0;
	len += ft_put_nbr(nbr, 0, fl);
	free(nbr);
	return (len);
}
