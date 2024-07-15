/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mult_strjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 23:32:46 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/26 14:34:30 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	mult_strlen(const char *deli, va_list args)
{
	size_t	len;
	size_t	del_len;
	char	*str;

	len = 0;
	del_len = ft_strlen(deli);
	str = va_arg(args, char *);
	while (str != NULL)
	{
		len += ft_strlen(str);
		str = va_arg(args, char *);
		if (str != NULL)
			len += del_len;
	}
	return (len);
}

/*
reverse of ft_split, joins strings with delimiter in between
l -  variadic function. accepts any amount of strings, last one must be NULL
*/
char	*ft_joinl(const char *delimiter, ...)
{
	va_list		args;
	const char	*str;
	char		*joined;
	size_t		len;

	va_start(args, delimiter);
	len = mult_strlen(delimiter, args);
	va_end(args);
	va_start(args, delimiter);
	joined = ft_calloc(1, len + 1);
	if (!joined)
		return (NULL);
	str = va_arg(args, char *);
	while (str != NULL)
	{
		ft_strlcat(joined, str, len + 1);
		str = va_arg(args, char *);
		if (str != NULL)
			ft_strlcat(joined, delimiter, len + 1);
	}
	va_end(args);
	return (joined);
}
