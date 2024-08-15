/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:56:09 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/10/16 18:40:31 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	start;
	size_t	end;

	trim = 0;
	if (s1 && set)
	{
		start = 0;
		end = ft_strlen(s1);
		while (s1[start] && ft_strchr(set, s1[start]))
			start++;
		while (ft_strchr(set, s1[end - 1]) && end > start)
			end--;
		trim = (char *)malloc(sizeof(*trim) * (end - start + 1));
		if (trim)
			ft_strlcpy(trim, &s1[start], (end - start + 1));
	}
	return (trim);
}
