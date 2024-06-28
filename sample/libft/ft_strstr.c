/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 06:32:35 by ychng             #+#    #+#             */
/*   Updated: 2024/02/21 06:48:41 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	haystack_len;
	int	needle_len;

	if (!haystack || !needle)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	haystack_len = ft_strlen(haystack);
	needle_len = ft_strlen(needle);
	while (*haystack && (haystack_len >= needle_len))
	{
		if (ft_strncmp(haystack, needle, needle_len) == 0)
			return ((char *)haystack);
		haystack++;
		haystack_len--;
	}
	return (NULL);
}
