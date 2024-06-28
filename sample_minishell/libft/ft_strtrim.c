/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:04:53 by ychng             #+#    #+#             */
/*   Updated: 2024/02/26 18:03:59 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strtrim(const char *str, const char *delim)
{
	char	*start;
	int		len;

	if (!str || !delim)
		return (NULL);
	start = (char *)str + ft_strspn(str, delim);
	len = ft_strlen(start) - ft_rstrspn(start, delim);
	return (ft_substr(start, 0, len));
}
