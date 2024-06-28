/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rstrspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:19:25 by ychng             #+#    #+#             */
/*   Updated: 2024/02/26 12:25:35 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_rstrspn(const char *str, const char *accept)
{
	int	span_len;
	int	len;

	if (!str || !accept)
		return (0);
	span_len = 0;
	len = ft_strlen(str);
	while (len > 0 && ft_strchr(accept, str[len - 1]))
	{
		span_len++;
		len--;
	}
	return (span_len);
}
