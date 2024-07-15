/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:24:31 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/15 16:10:10 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"
#include <math.h>

int	plus(int x, int y)
{
	return (x + y);
}

int	minus(int x, int y)
{
	return (x - y);
}

int	multiply(int x, int y)
{
	return (x * y);
}

int	divide(int x, int y)
{
	if (y == 0)
	{
		error_msg("Error! Dividing by zero.");
		return (0);
	}
	else
		return (x / y);
}

int	power(int x, int y)
{
	return (pow(x, y));
}
