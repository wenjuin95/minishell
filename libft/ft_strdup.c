/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:57:02 by welow             #+#    #+#             */
/*   Updated: 2024/06/09 14:22:24 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
*	@brief	create a duplicate of a string (memory allocation)
*	@param	s :: the string to duplicate
*	@return	char* :: the duplicate of the string
*	@note	need to free the returned pointer
*/
char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	i;
	size_t	size;

	size = 0;
	while (s[size])
		size++;
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int main()
// {
// 	char *str = "world";

// 	char *dup = strdup(str);
// 	char *dup2 = ft_strdup(str);
// 	if(dup == NULL || dup2 == NULL)
// 		return 0;
// 	dup[0] = 'd';
// 	dup2[0] = 'd';
// 	printf("original:%s\n", str);
// 	printf("strdup:%s\n", dup);
// 	printf("ft_strdup:%s\n", dup2);

// 	free(dup);	
// }
