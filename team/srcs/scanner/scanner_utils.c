/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:04:29 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/21 21:01:39 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_scanner(t_scanner *scanner, const char *line)
{
	scanner->current = line;
	scanner->start = line;
}

/* 
auxiliary function for make_operator_token()
checks if next char is expected char
if true, returns iftrue token type and moves current front by 1
*/
t_token	match_next(char expect, t_ttype iftrue, t_ttype iffalse, t_scanner *s)
{
	t_token	token;

	if (*s->current == '\0')
		token.type = iffalse;
	if (*s->current != expect)
		token.type = iffalse;
	else
	{
		token.type = iftrue;
		s->current++;
	}
	token.value = NULL;
	return (token);
}
