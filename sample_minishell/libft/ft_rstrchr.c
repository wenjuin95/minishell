/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rstrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 07:57:59 by ychng             #+#    #+#             */
/*   Updated: 2024/03/24 08:04:51 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_rstrchr(const char *str, int c)
{
	const char	*last_found;

	last_found = NULL;
	while (str && *str)
	{
		if (*str == (char)c)
			last_found = str;
		str++;
	}
	return ((char *)last_found);
}
