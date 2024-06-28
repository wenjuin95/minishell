/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rstrcspn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 07:48:49 by ychng             #+#    #+#             */
/*   Updated: 2024/03/24 07:51:27 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_rstrcspn(const char *str, const char *reject)
{
	int	span_len;
	int	len;

	if (!str || !reject)
		return (0);
	span_len = 0;
	len = ft_strlen(str);
	while (len > 0 && !ft_strchr(reject, str[len - 1]))
	{
		span_len++;
		len--;
	}
	return (span_len);
}
