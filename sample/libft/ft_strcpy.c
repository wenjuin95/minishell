/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:58:35 by ychng             #+#    #+#             */
/*   Updated: 2024/02/20 15:01:33 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*start;

	if (!dest || !src)
		return (dest);
	start = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (start);
}
