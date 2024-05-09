/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:03:35 by welow             #+#    #+#             */
/*   Updated: 2024/01/28 23:08:29 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_format(va_list list_argument, const char str)
{
	int		count;

	count = 0;
	if (str == 'c')
		count += ft_putchar(va_arg(list_argument, int));
	else if (str == 's')
		count += ft_putstr(va_arg(list_argument, char *));
	else if (str == 'd' || str == 'i')
		count += ft_putnbr(va_arg(list_argument, int));
	else if (str == 'u')
		count += ft_putnbr_unsigned(va_arg(list_argument, unsigned int));
	else if (str == 'x')
		count += ft_puthexa_lower(va_arg(list_argument, unsigned int));
	else if (str == 'X')
		count += ft_puthexa_upper(va_arg(list_argument, unsigned int));
	else if (str == 'p')
		count += ft_putaddress(va_arg(list_argument, unsigned long long));
	else if (str == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list		list_argument;
	int			i;
	int			count;

	i = 0;
	count = 0;
	va_start(list_argument, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += printf_format(list_argument, format[i + 1]);
			i++;
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(list_argument);
	return (count);
}
