/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 20:36:38 by ychng             #+#    #+#             */
/*   Updated: 2024/03/06 01:00:17 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	calc_total_len(const char *s1, const char *s2, const char *delim)
{
	return (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(delim));
}

char	*ft_strjoin(const char *s1, const char *s2, const char *delim)
{
	int		total_len;
	char	*result;

	if (!s1 && !s2 && !delim)
		return (NULL);
	total_len = calc_total_len(s1, s2, delim);
	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	if (delim)
		ft_strcat(result, delim);
	ft_strcat(result, s2);
	return (result);
}
