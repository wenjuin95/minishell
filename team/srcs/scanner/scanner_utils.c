/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:04:29 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/02 12:33:39 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief Initialize scanner
*	@param scanner Scanner
*	@param line Line to scan
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
*	@param expect Expected char
*	@param iftrue Token type if next char is expected char
*	@param iffalse Token type if next char is not expected char
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

	if (*s->current == '\0') //if end of line
		token.type = iffalse; //return iffalse token type
	if (*s->current != expect) //if next char is not expected char
		token.type = iffalse; //return iffalse token type
	else
	{
		token.type = iftrue; //return iftrue token type
		s->current++; //move current front by 1
	}
	token.value = ft_strdup(tok_values[token.type]); //assign token value
	return (token); //return token
}
