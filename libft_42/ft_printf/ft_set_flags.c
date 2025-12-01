/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:47:15 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/12/02 16:33:20 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_flags	set_width_flag(char c, t_flags flags)
{
	flags.width = (flags.width * 10) + (c - '0');
	return (flags);
}

static t_flags	set_left_flag(t_flags flags)
{
	flags.zero = 0;
	flags.left = 1;
	return (flags);
}

static char	*set_precision_flag(char *s, t_flags *flags)
{
	flags->dot = 1;
	flags->precision = 0;
	while (ft_is_digit(*++s))
		flags->precision = (flags->precision * 10) + (*s - '0');
	return (s);
}

t_flags	set_flag(char *s)
{
	t_flags	flags;

	flags = new_flag();
	while (*s && !ft_str_chr(SPECIFIER, *s))
	{
		if (*s == '#')
			flags.hash = 1;
		if (*s == '0' && !ft_is_digit(*(s - 1)) && flags.left == 0)
			flags.zero = 1;
		if (*s == '-')
			flags = set_left_flag(flags);
		if (*s == ' ')
			flags.space = 1;
		if (*s == '+')
			flags.plus = 1;
		if (ft_is_digit(*s))
			flags = set_width_flag(*s, flags);
		if (*s == '.')
			s = set_precision_flag(s, &flags);
		if (!ft_str_chr(SPECIFIER, *s))
			s++;
	}
	flags.spec = *s;
	return (flags);
}
