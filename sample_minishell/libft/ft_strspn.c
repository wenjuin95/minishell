/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:33:57 by ychng             #+#    #+#             */
/*   Updated: 2024/02/17 17:53:33 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_strspn(const char *str, const char *accept)
{
	int	span_len;

	if (!str || !accept)
		return (0);
	span_len = 0;
	while (str[span_len] && ft_strchr(accept, str[span_len]))
		span_len++;
	return (span_len);
}
