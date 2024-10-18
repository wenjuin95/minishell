/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:02:53 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/09/11 14:16:03 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@breif replace a substring in a string with another substring
*/
char	*ft_str_replace(char *str, char *rep, char *with)
{
	char	*result;
	size_t	new_len;
	char	*insert_pos;
	char	*tmp;

	new_len = ft_strlen(str) + (ft_strlen(with) - ft_strlen(rep));
	result = ft_calloc(new_len + 1, sizeof(char));
	if (!result)
		return (NULL);
	tmp = result;
	insert_pos = ft_strnstr(str, rep, ft_strlen(str));
	ft_strlcpy(tmp, str, (insert_pos - str) + 1);
	tmp += (insert_pos - str);
	ft_strlcpy(tmp, with, ft_strlen(with) + 1);
	tmp += ft_strlen(with);
	str += (insert_pos - str) + ft_strlen(rep);
	ft_strlcpy(tmp, str, ft_strlen(str) + 1);
	return (result);
}
