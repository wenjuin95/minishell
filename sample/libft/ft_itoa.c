/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:57:40 by ychng             #+#    #+#             */
/*   Updated: 2024/02/13 18:18:28 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static void	add_into_buffer(long n, char *buffer)
{
	int		i;
	long	temp;

	i = 0;
	temp = n;
	if (n == 0)
		buffer[i++] = '0';
	if (n < 0)
		n *= -1;
	while (n)
	{
		buffer[i++] = n % 10 + '0';
		n /= 10;
	}
	if (temp < 0)
		buffer[i++] = '-';
	buffer[i] = '\0';
}

static void	ft_reverse(char *buffer, char *result)
{
	int	length;
	int	i;

	length = ft_strlen(buffer);
	i = 0;
	while (length--)
		result[i++] = buffer[length];
	result[i] = '\0';
}

char	*ft_itoa(int n)
{
	char	buffer[12];
	char	*result;

	add_into_buffer(n, buffer);
	result = malloc(sizeof(char) * (ft_strlen(buffer) + 1));
	if (!result)
		return (NULL);
	ft_reverse(buffer, result);
	return (result);
}
