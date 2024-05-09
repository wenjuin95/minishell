/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:00:14 by welow             #+#    #+#             */
/*   Updated: 2023/10/16 12:00:14 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *haystack, char const *needle, size_t n)
{
	size_t	i;
	size_t	j;

	if (n == 0 && haystack == 0)
		return (0);
	i = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[i] && i < n)
	{
		j = 0;
		while (needle[j] && needle[j] == haystack[i + j] && i + j < n)
		{
			if (needle[j + 1] == '\0')
			{
				return ((char *)haystack + i);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <stdlib.h>
// int main() {
//     const char *haystack = "The quick brown fox jumps over the lazy dog";
//     const char *needle = "fox";
// 	size_t len = 30;

//     char *result = ft_strnstr(haystack, needle, len);

// 	printf("In this string:'The quick brown fox jumps over the lazy dog'\n");
// 	  if (result != NULL) {
//         printf("found at %ld in %zu characters.\n", result-haystack, len);
//     } else {
//         printf("not found within the first %zu characters.\n", len);
//     }
// }
