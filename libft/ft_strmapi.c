/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:00:03 by welow             #+#    #+#             */
/*   Updated: 2023/10/16 12:00:03 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*result;

	if (s == NULL)
		return (NULL);
	i = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (result == NULL)
		return (NULL);
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

// #include <stdio.h>
// #include <ctype.h>

// char uppercase(unsigned int i, char c)
// {
// 	(void)i;
//     return toupper(c);
// }

// int main() {
//     char str[] = "hello, world!";

//     printf("Original string: %s\n", str);

//     // Apply the capitalize function to each character in the string
//     char *result = ft_strmapi(str, &uppercase);

//     printf("Capitalized string: %s\n", result);
// 	free(result);

//     return 0;
// }