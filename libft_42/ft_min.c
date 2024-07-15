/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:32:35 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/02/01 17:22:04 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_min(int count, ...)
{
	int		i;
	int		min;
	int		num;
	va_list	args;

	va_start(args, count);
	i = 1;
	min = va_arg(args, int);
	while (i < count)
	{
		num = va_arg(args, int);
		if (num < min)
			min = num;
		i++;
	}
	va_end(args);
	return (min);
}
