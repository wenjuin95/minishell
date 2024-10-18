/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 21:21:06 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/10/18 13:32:30 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdbool.h>

static void	free_lookup(bool **lookup, int s_len);

static void	is_match_check(char *pattern, char *str, bool **match_lookup)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (i <= ft_strlen(str))
	{
		j = 1;
		while (j <= ft_strlen(pattern))
		{
			if (pattern[j - 1] == '*')
				match_lookup[i][j]
					= (match_lookup[i - 1][j] || match_lookup[i][j - 1]);
			else if (pattern[j - 1] == '?' || pattern[j - 1] == str[i - 1])
				match_lookup[i][j] = match_lookup[i - 1][j - 1];
			j++;
		}
		i++;
	}
}

bool	is_match(char *pattern, char *str)
{
	bool	**match_lookup;
	int		i;
	int		s_len;
	int		p_len;
	bool	result;

	s_len = ft_strlen(str);
	p_len = ft_strlen(pattern);
	match_lookup = ft_calloc(s_len + 1, sizeof(bool *));
	i = -1;
	while (++i <= s_len)
		match_lookup[i] = ft_calloc(p_len + 1, sizeof(bool));
	match_lookup[0][0] = true;
	i = 1;
	while (i <= p_len)
	{
		if (pattern[i - 1] == '*')
			match_lookup[0][i] = match_lookup[0][i - 1];
		i++;
	}
	is_match_check(pattern, str, match_lookup);
	result = match_lookup[s_len][p_len];
	free_lookup(match_lookup, s_len);
	return (result);
}

static void	free_lookup(bool **lookup, int s_len)
{
	int	i;	

	i = -1;
	while (++i <= s_len)
		free(lookup[i]);
	free(lookup);
}
