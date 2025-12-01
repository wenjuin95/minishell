/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:16:54 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/10/15 12:35:53 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	if (c == 0)
		return ((char *)(s + i));
	while (i > 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	if (s[0] == (char)c)
		return ((char *)s);
	return (0);
}
