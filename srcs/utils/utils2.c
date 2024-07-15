/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:17:15 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/14 16:21:33 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
man getenv
goes through the environmentable variables (which are "name=value" pairs) 
and searches for a string with the requested name and returns the value
*/
char	*ft_getenv(char *name, char *const envp[])
{
	char	**e_ptr;
	int		len;

	if (!envp || !name)
		return (NULL);
	e_ptr = (char **)envp;
	len = ft_strlen(name);
	while (*e_ptr)
	{
		if (ft_strnstr(*e_ptr, name, len))
			return (*e_ptr + len + 1);
		e_ptr++;
	}
	return (NULL);
}
