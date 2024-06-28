/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:26:27 by ychng             #+#    #+#             */
/*   Updated: 2024/02/18 21:42:32 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strndup(const char *str, int n)
{
	int		copy_len;
	char	*new_str;

	if (!str || n < 0)
		return (NULL);
	copy_len = ft_strlen(str);
	if (copy_len > n)
		copy_len = n;
	new_str = malloc(sizeof(char) * (copy_len + 1));
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, str, copy_len);
	new_str[copy_len] = '\0';
	return (new_str);
}
