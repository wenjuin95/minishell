/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:25:09 by ychng             #+#    #+#             */
/*   Updated: 2024/02/18 19:29:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_strcspn(const char *str, const char *reject)
{
	int	span_len;

	if (!str || !reject)
		return (0);
	span_len = 0;
	while (str[span_len] && !ft_strchr(reject, str[span_len]))
		span_len++;
	return (span_len);
}
