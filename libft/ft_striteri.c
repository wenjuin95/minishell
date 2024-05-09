/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:57:10 by welow             #+#    #+#             */
/*   Updated: 2023/10/16 11:57:10 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	if (s == 0 || f == 0)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}

// #include <stdio.h>
// #include <ctype.h>

// void uppercase(unsigned int index, char *ch)
// {
// 	(void)index;
// 	*ch = toupper(*ch);
// }

// int main() {
//     char str[] = "hello world";

//     printf("Original string: %s\n", str);

//     // Apply the capitalize function to each character in the string
//     ft_striteri(str, uppercase);

//     printf("Capitalized string: %s\n", str);

//     return 0;
// }
