/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:30:36 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/10/16 20:26:20 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	count_len(int nbr)
{
	size_t			len;
	unsigned int	abs_nb;

	len = 0;
	if (nbr < 0)
	{
		abs_nb = nbr * -1;
		len++;
	}
	else
		abs_nb = nbr;
	while (abs_nb >= 10)
	{
		abs_nb /= 10;
		len++;
	}
	len++;
	return (len);
}

static	void	putnbr_str(char *nstr, int nbr, size_t len)
{
	unsigned int	nb;

	if (nbr < 0)
	{
		nstr[0] = '-';
		nb = nbr * -1;
	}
	else
		nb = nbr;
	while (nb >= 10)
	{
		nstr[len] = (nb % 10) + '0';
		nb /= 10;
		len--;
	}
	if (nb < 10)
		nstr[len] = nb + '0';
}

char	*ft_itoa(int n)
{
	char	*nstr;
	size_t	len;

	len = count_len(n);
	nstr = (char *)malloc(sizeof(*nstr) * (len + 1));
	if (nstr == NULL)
		return (nstr);
	putnbr_str(nstr, n, len - 1);
	nstr[len] = 0;
	return (nstr);
}
