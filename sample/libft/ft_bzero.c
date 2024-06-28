/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:58:53 by ychng             #+#    #+#             */
/*   Updated: 2024/03/06 18:04:16 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*string;

	string = (unsigned char *)str;
	while (n--)
		*string++ = 0;
}
