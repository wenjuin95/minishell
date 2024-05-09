/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:00:38 by welow             #+#    #+#             */
/*   Updated: 2023/10/16 12:00:38 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 97 + 65);
	return (c);
}

// #include <ctype.h>
// #include <stdio.h>
// int main()
// {
//     char str[] = "geekforgeeks\n";
//     char ch;
//     char ch2;
//     int i = 0;
//     int j = 0;
//     while (str[j]) {
//         ch = str[j];
//         putchar(toupper(ch));
//         j++;
//     }
//     while (str[i])
//     {
//         ch2 = str[i];
//         putchar(ft_toupper(ch2));
//         i++;
//     }
// }
