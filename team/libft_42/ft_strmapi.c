/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:32:09 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/11/02 16:54:21 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*mstr;

	if (!f || !s)
		return (NULL);
	len = ft_strlen(s);
	mstr = (char *)malloc((sizeof(*mstr) * len + 1));
	if (mstr != NULL)
	{
		i = 0;
		while (i < len)
		{
			mstr[i] = f(i, s[i]);
			i++;
		}
		mstr[i] = 0;
	}
	return (mstr);
}
