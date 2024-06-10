/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:55:14 by welow             #+#    #+#             */
/*   Updated: 2024/06/09 14:12:50 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
*	@brief	check if a character is a digit
*	@param	c :: the character to check
*	@return	non-zero if true, 0 if false
*/
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (2048);
	}
	return (0);
}

// #include <stdio.h>
// #include <ctype.h>
// int main()
// {
//     char b = '9';
//     printf("%d\n", ft_isdigit(b));
//     printf("%d\n", isdigit(b));
// }
