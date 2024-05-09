/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:00:33 by welow             #+#    #+#             */
/*   Updated: 2023/10/16 12:00:33 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c - 65 + 97);
	return (c);
}

// #include <ctype.h>
// #include <stdio.h>
// int main()
// {
//     char str[] = "GEEKFORGEEKS\n";
//     char ch;
//     char ch2;
//     int i = 0;
//     int j = 0;
//     while (str[j]) {
//         ch = str[j];
//         putchar(tolower(ch));
//         j++;
//     }
//     while (str[i])
//     {
//         ch2 = str[i];
//         putchar(ft_tolower(ch2));
//         i++;
//     }
// }