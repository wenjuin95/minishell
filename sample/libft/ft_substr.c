/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:31:37 by ychng             #+#    #+#             */
/*   Updated: 2024/02/13 20:57:53 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_substr(const char *str, int start, int len)
{
	int		str_len;
	int		substr_len;
	char	*substr;
	int		i;

	if (!str || start < 0 || len < 0)
		return (NULL);
	str_len = ft_strlen(str);
	if (start >= str_len)
		return (NULL);
	if ((str_len - start) < len)
		substr_len = (str_len - start);
	else
		substr_len = len;
	substr = malloc(sizeof(char) * (substr_len + 1));
	if (!substr)
		return (NULL);
	i = -1;
	while (++i < substr_len)
		substr[i] = str[start + i];
	substr[i] = '\0';
	return (substr);
}
