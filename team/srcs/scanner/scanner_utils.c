/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:04:29 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/27 13:22:57 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief	initialize scanner
*	@param	line :: line to scan
*	@return	struct scanner with start and current position
*/
t_scanner	init_scanner(const char *line)
{
	t_scanner	scanner;

	scanner.current = line; //current position is at the start of the line
	scanner.start = line; //start of the line
	return (scanner);
}

/* 
*	@brief make token
*	@param expect :: expected character
*	@param iftrue :: token type if expected character is found
*	@param iffalse :: token type if expected character is not found
*	@param s :: scanner struct
*	@return struct token with type and value
*
*	auxiliary function for make_operator_token()
*	checks if next char is expected char
*	if true, returns iftrue token type and moves current front by 1
*/
t_token	match_next(char expect, t_ttype iftrue, t_ttype iffalse, t_scanner *s)
{
	t_token	token;

	if (*s->current == '\0') //if end of string
		token.type = iffalse; 
	if (*s->current != expect) //if next char is not expected char
		token.type = iffalse; 
	else //if next char is expected char
	{
		token.type = iftrue;
		s->current++; //move to next char
	}
	token.value = NULL; //value is NULL
	return (token); //return token
}
