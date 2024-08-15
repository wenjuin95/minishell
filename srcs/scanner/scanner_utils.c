/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:04:29 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/08/12 13:54:33 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief get the current line and start line and store in scanner
*	@param scanner the scanner struct
*	@param line the string to be scanned
*/
void	init_scanner(t_scanner *scanner, const char *line)
{
	scanner->current = line;
	scanner->start = line;
}

/* 
*	@brief 1. auxiliary function for make_operator_token()
*	@brief 2. checks if next char is expected char
*	@param  expect character to checked
*	@param  iftrue token type if true
*	@param  iffalse token type if false
*	@param  s scanner struct
*	@return 1. if false, returns iffalse token type
*	@return 2. if true, returns iftrue token type 
			and moves current front by 1
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

	if (*s->current == '\0')
		token.type = iffalse;
	if (*s->current != expect)
		token.type = iffalse;
	else
	{
		token.type = iftrue;
		s->current++;
	}
	token.value = ft_strdup(tok_values[token.type]);
	return (token);
}
