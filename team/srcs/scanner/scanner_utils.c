/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:04:29 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/11 17:35:25 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief initialize the scanner struct
*	@param scanner: scanner struct
*	@param line: string to scan
*/
void	init_scanner(t_scanner *scanner, const char *line)
{
	scanner->current = line;
	scanner->start = line;
}

/* 
*	auxiliary function for make_operator_token()
*	checks if next char is expected char
*	if true, returns iftrue token type and moves current front by 1
*	if false, returns iffalse token type
*/
t_token	match_next(char expect, t_tok_type iftrue, t_tok_type iffalse,
	t_scanner *s)
{
	t_token		token;
	const char	*tok_values[] = {
	[TOK_DLESS] = "<<", [TOK_LESS] = "<",
	[TOK_DGREAT] = ">>", [TOK_GREAT] = ">",
	[TOK_OR_IF] = "||", [TOK_PIPE] = "|",
	[TOK_AND_IF] = "&&"
	};

	if (*s->current == '\0') //if the current char is null
		token.type = iffalse; 
	if (*s->current != expect) //if the current char is not the expected char
		token.type = iffalse; 
	else //if the current char is the expected char
	{
		token.type = iftrue;
		s->current++;
	}
	token.value = ft_strdup(tok_values[token.type]); //set the token value
	return (token);
}