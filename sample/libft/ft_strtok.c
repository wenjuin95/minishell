/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:58:45 by ychng             #+#    #+#             */
/*   Updated: 2024/03/11 13:19:20 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	skip_leading_delims(char *remaining_str, const char *delim)
{
	return (ft_strspn(remaining_str, delim));
}

static int	find_end_of_token(char *remaining_str, const char *delim)
{
	return (ft_strcspn(remaining_str, delim));
}

static char	*terminate_and_move(char *remaining_str)
{
	if (*remaining_str)
		*remaining_str++ = '\0';
	return (remaining_str);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*remaining_str;
	char		*token;

	if (str != NULL)
		remaining_str = str;
	if (remaining_str == NULL || *remaining_str == '\0')
		return (NULL);
	remaining_str += skip_leading_delims(remaining_str, delim);
	token = remaining_str;
	remaining_str += find_end_of_token(remaining_str, delim);
	remaining_str = terminate_and_move(remaining_str);
	return (token);
}
