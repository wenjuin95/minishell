/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 01:18:03 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/12/30 21:43:51 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* SPECIFIER "cspdiuxX%" */
int	parse_flags(const char *s, va_list args)
{
	t_flags	flags;
	int		(*f_conv[9])(va_list, t_flags);
	int		i;
	int		len;

	flags = set_flag((char *)s);
	f_conv[0] = print_char;
	f_conv[1] = print_string;
	f_conv[2] = print_ptr;
	f_conv[3] = print_dec;
	f_conv[4] = print_dec;
	f_conv[5] = print_u;
	f_conv[6] = print_hex;
	f_conv[7] = print_hex;
	f_conv[8] = print_char;
	i = -1;
	while (SPECIFIER[++i])
		if (flags.spec == SPECIFIER[i])
			len = (f_conv[i])(args, flags);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;

	if (!format || *format == '\0')
		return (0);
	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[++i])
				len += parse_flags(&format[i], args);
			while (format[i] && !ft_str_chr(SPECIFIER, format[i]))
				i++;
		}
		else
			len += ft_putchar2(format[i]);
		if (format[i])
			i++;
	}
	va_end(args);
	return (len);
}
