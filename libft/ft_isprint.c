/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:55:21 by welow             #+#    #+#             */
/*   Updated: 2023/10/16 11:55:21 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
*	@brief	check if a character is printable
*	@param	c :: the character to check
*	@return	non-zero if true, 0 if false
*/
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
	{
		return (16384);
	}
	return (0);
}

// #include <stdio.h>
// #include <ctype.h>
// int main()
// {
//     char c = 127;
// 	printf("%d\n", ft_isprint(c));
// 	printf("%d\n", isprint(c)); //return 16384
// }
