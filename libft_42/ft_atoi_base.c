/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:33:05 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/01/23 17:20:52 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_digit(char c, int base)
{
	int	i;

	i = 0;
	while (i < base)
	{
		if (c == HEXLOW[i] || c == HEXUP[i])
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(const char *nptr, int base)
{
	int	val;
	int	neg;

	neg = 1;
	val = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			neg = -1;
		nptr++;
	}
	while (get_digit(*nptr, base) != -1)
	{
		val = (val * base) + get_digit(*nptr, base);
		nptr++;
	}
	return (val * neg);
}
