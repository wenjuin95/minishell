/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 00:37:46 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/11/02 16:57:12 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != '\0')
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static char	*make_str(const char *s, char c)
{
	char	*str;
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, len + 1);
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	count;
	size_t	i;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	strs = (char **)malloc(sizeof(*strs) * (count + 1));
	if (!strs)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != '\0')
		{
			strs[i] = make_str(s, c);
			i++;
		}
		while (*s != c && *s)
			s++;
	}
	strs[i] = 0;
	return (strs);
}
