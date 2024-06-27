/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:51:28 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/27 13:27:45 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* characters that when unquoted, separates words*/
#define METACHAR "|&;<>() \t\n"
#define OPERATOR "|&<>()"

/*
*	@brief	make string token
*	@param	type :: type of token
*	@param	string :: string value
*	@return	new token
*/
t_token	make_token(t_ttype type, char *string)
{
	t_token	new_token;

	new_token.type = type;
	new_token.value = string;
	return (new_token);
}

/*
*	@brief	check if next character is quote
*	@param	scanner :: struct scanner
*	@param	quote_type :: type of quote
*	@return	0 if found, -1 if not found
*/
int	quotes(t_scanner *scanner, char quote_type)
{
	while (*scanner->current != '\0' && *scanner->current != quote_type)
		scanner->current++; //if not found, move to next character
	if (*scanner->current == '\0' && *scanner->current != quote_type)
		return (-1); //if whole string not found, return -1
	return (0); //if found, return 0
}

/*
*	@brief word tokenization
*	@param	scanner :: struct scanner
*	@return	struct token with type and value
*/
t_token	make_word_token(t_scanner *scanner)
{
	char	*word;
	char	c;

	scanner->current--; //move back to the last character
	while (!ft_strchr(METACHAR, *scanner->current)) //look for METACHAR
	{
		c = *(scanner->current++); //move to next character
		if (c == '\'' || c == '"') //if c is single or double quote
		{
			if (quotes(scanner, c) == -1) //if quote not found
				return (make_token(TOK_ERROR, "Unclosed quotes")); //return type: error, value: unclosed quotes
			scanner->current++; //move to next character
		}
	}
	word = ft_substr(scanner->start, 0, (scanner->current - scanner->start)); //get the word
	return (make_token(TOK_WORD, word)); //return type: word, value: word
}

/* 
*	@brief	match next character
*	@param	curr :: current character
*	@param	scanner :: struct scanner
*	@return	struct token with type and value
*
*	for single character operators it returns its type
*	for double character ones it checks it with match_next()
*	Notes: the function will not reach the last line 
*/
t_token	make_operator_token(char curr, t_scanner *scanner)
{
	if (curr == '(')
		return (make_token(TOK_LPAREN, NULL)); //return type: left parenthesis
	if (curr == ')')
		return (make_token(TOK_RPAREN, NULL)); //return type: right parenthesis
	if (curr == '<')
		return (match_next('<', TOK_DLESS, TOK_LESS, scanner)); //if next char is '<', return type: double less, else return type: less
	if (curr == '>')
		return (match_next('>', TOK_DGREAT, TOK_GREAT, scanner)); //if next char is '>', return type: double great, else return type: great
	if (curr == '|')
		return (match_next('|', TOK_OR_IF, TOK_PIPE, scanner)); //if next char is '|', return type: or if, else return type: pipe
	if (curr == '&')
		return (match_next('&', TOK_AND_IF, TOK_ERROR, scanner)); //if next char is '&', return type: and if, else return type: error
	return (make_token(TOK_ERROR, NULL)); //if character is not supported above, return type: error
}

/* 
Scans the string and returns the next word/operator
Returns a error token upon seeing a unsupported character 
*/
t_token	next_token(t_scanner *scanner)
{
	char	curr;

	while (ft_isspace(*scanner->current)) //if current character is space
		scanner->current++;
	scanner->start = scanner->current;
	if (*scanner->current == '\0') //if end of string
		return (make_token(TOK_EOF, NULL)); //return type: end of file
	curr = *scanner->current; //get current character
	scanner->current++; //move to next character
	if (ft_strchr(OPERATOR, curr)) //if current character is operator
		return (make_operator_token(curr, scanner)); //return type: operator, value: operator
	if (!ft_strchr(METACHAR, curr)) //if current character is not METACHAR
		return (make_word_token(scanner)); //return type: word, value: word
	return (make_token(TOK_ERROR, "Unexpected Character")); //if character is not supported above, return type: error, value: unexpected character
}
