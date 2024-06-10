/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:57:15 by welow             #+#    #+#             */
/*   Updated: 2024/06/09 14:23:36 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
*	@brief	join two strings together
*	@param	s1 :: the first string
*	@param	s2 :: the second string
*	@return	char* :: the new string
*	@note	need to free the returned pointer
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;
	int		total_len;

	if (s1 == 0 || s2 == 0)
		return (0);
	i = 0;
	j = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (total_len + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i++] = s2[j++];
	}
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>

int main()
{
	char str1[] = "hello";
	char str2[] = " world";
	char *result = ft_strjoin(str1, str2);
	printf("%s\n", result);
}*/
