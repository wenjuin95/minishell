/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 22:22:26 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/11/02 16:55:36 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	else if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub = (char *)malloc(sizeof(*sub) * (len + 1));
	if (sub == NULL)
		return (sub);
	i = start;
	j = 0;
	while (j < len && s[i])
	{
		sub[j] = s[i];
		i++;
		j++;
	}
	sub[j] = 0;
	return (sub);
}
