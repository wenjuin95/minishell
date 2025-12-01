/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:28:35 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/10/25 16:54:53 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check for wildcard symbols(* and ?) in string
static bool	check_wildcard(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
	{
		if (*ptr == '*' || *ptr == '?')
			return (true);
		ptr++;
	}
	return (false);
}

static bool	checkdotfiles(char *str, char *entry_name)
{
	if (entry_name[0] != '.' || str[0] == '.')
		return (true);
	else
		return (false);
}

t_list	*expand_wildcard(char *str)
{
	DIR				*directory;
	struct dirent	*entry;
	t_list			*matches;

	if (check_wildcard(str) == false)
		return (ft_lstnew(str));
	directory = opendir(".");
	matches = NULL;
	entry = readdir(directory);
	while (entry != NULL)
	{
		if (is_match(str, entry->d_name))
		{
			if (checkdotfiles(str, entry->d_name))
				ft_lstadd_back(&matches, ft_lstnew(ft_strdup(entry->d_name)));
		}
		entry = readdir(directory);
	}
	closedir(directory);
	if (!matches)
	{
		return (ft_lstnew(str));
	}
	free(str);
	return (matches);
}
