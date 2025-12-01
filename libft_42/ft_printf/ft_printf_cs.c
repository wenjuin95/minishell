/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:53:45 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/12/30 21:42:57 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* possible flags : -,width */
int	print_char(va_list args, t_flags flags)
{
	char	c;
	int		len;

	len = 0;
	if (flags.spec == '%')
		c = '%';
	else
		c = va_arg(args, int);
	flags.precision = 1;
	if (flags.left == 1)
		len += ft_putchar2(c);
	len += put_padding(flags.width, flags.precision, flags.zero);
	if (flags.left == 0)
		len += ft_putchar2(c);
	return (len);
}

/*possible flags : -,precision,width */
int	print_string(va_list args, t_flags flags)
{
	char	*s;
	int		len;
	size_t	s_len;

	len = 0;
	s = va_arg(args, char *);
	if (!s)
		s = "(null)";
	s_len = ft_str_len(s);
	if (flags.precision >= 0 && (size_t)flags.precision > s_len)
		flags.precision = s_len;
	if (flags.left == 1)
		len += ft_putstr_prec(s, flags.precision);
	if (flags.precision >= 0)
		len += put_padding(flags.width, flags.precision, flags.zero);
	else
		len += put_padding(flags.width, s_len, flags.zero);
	if (flags.left == 0)
		len += ft_putstr_prec(s, flags.precision);
	return (len);
}
