/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:54:56 by welow             #+#    #+#             */
/*   Updated: 2023/10/16 11:54:59 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
	{
		return (1024);
	}
	return (0);
}

// #include <stdio.h>
// #include <ctype.h>
// int main()
// {
// 	char c = 'z';
// 	printf("%d\n", ft_isalpha(c));
// 	printf("%d\n", isalpha(c));
// }
