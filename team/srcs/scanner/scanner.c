/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:51:28 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/02 12:40:47 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* characters that when unquoted, separates words*/
#define METACHAR "|&;<>() \t\n"
#define OPERATOR "|&<>()"

/*
*	@brief Create new token
*	@param type Token type
*	@param string Token value
*	@return New token
*/
t_token	make_token(t_tok_type type, char *string)
{
	t_token	new_token;

	new_token.type = type;
	new_token.value = string;
	return (new_token);
}

/*
*	@brief Check if character has quote
*	@param scanner Scanner
*	@param quote_type Quote type
*	@return 0 if quote found, -1 if quote not found
*/
int	quotes(t_scanner *scanner, char quote_type)
{
	while (*scanner->current != '\0' && *scanner->current != quote_type) //if the current character is not end of line and not quote
		scanner->current++;
	if (*scanner->current == '\0' && *scanner->current != quote_type) //if the current character is end of line and not quote
		return (-1);
	return (0);
}

/*
*	@brief Create word token
*	@param scanner Scanner
*	@return New token
*/
t_token	make_word_token(t_scanner *scanner)
{
	char	*word;
	char	c;

	scanner->current--; //move current back by 1 for checking METACHAR
	while (!ft_strchr(METACHAR, *scanner->current)) //if current character is not METACHAR
		scanner->current++; //move current front by 1
	{
		c = *(scanner->current++); //assign current character to c and move current front by 1
		if (c == '\'' || c == '"') //if c is quote or double quote
		{
			if (quotes(scanner, c) == -1) //if quote not found
				return (make_token(TOK_ERROR, "Unclosed quotes")); //return error token
			scanner->current++; //move current front by 1
		}
	}
	word = ft_substr(scanner->start, 0, (scanner->current - scanner->start)); //assign word from start to current without METACHAR
	return (make_token(TOK_WORD, word)); //return word token
}

/* 
*	for single character operators it returns its type
*	for double character ones it checks it with match_next()
*	Notes: the function will not reach the last line
*	@param curr Current character
*	@param scanner Scanner
*	@return New token
*/
t_token	make_operator_token(char curr, t_scanner *scanner)
{
	if (curr == '(') 
		return (make_token(TOK_LPAREN, ft_strdup("("))); //if current character is '(' return LPAREN token
	if (curr == ')')
		return (make_token(TOK_RPAREN, ft_strdup(")"))); //if current character is ')' return RPAREN token
	if (curr == '<')
		return (match_next('<', TOK_DLESS, TOK_LESS, scanner)); //if current character is '<' check for the next character and return DLESS or LESS token
	if (curr == '>')
		return (match_next('>', TOK_DGREAT, TOK_GREAT, scanner)); //if current character is '>' check for the next character and return DGREAT or GREAT token
	if (curr == '|')
		return (match_next('|', TOK_OR_IF, TOK_PIPE, scanner)); //if current character is '|' check for the next character and return OR_IF or PIPE token
	if (curr == '&')
		return (match_next('&', TOK_AND_IF, TOK_ERROR, scanner)); //if current character is '&' check for the next character and return AND_IF or ERROR token
	return (make_token(TOK_ERROR, NULL)); //return ERROR token if not supported character
}

/* 
*	Scans the string and returns the next word/operator
*	Returns a error token upon seeing a unsupported character 
*	@param scanner Scanner
*	@return New token
*/
t_token	scan_token(t_scanner *scanner)
{
	char	curr;

	while (ft_isspace(*scanner->current)) //if current character is space
		scanner->current++;
	scanner->start = scanner->current; //assign current to start
	if (*scanner->current == '\0') //if current character is end of line
		return (make_token(TOK_EOF, NULL));
	curr = *scanner->current; //assign current character to curr
	scanner->current++; //move current front by 1 for checking METACHAR
	if (ft_strchr(OPERATOR, curr)) //if current character is OPERATOR
		return (make_operator_token(curr, scanner));
	if (!ft_strchr(METACHAR, curr)) //if current character is not METACHAR
		return (make_word_token(scanner));
	return (make_token(TOK_ERROR, "Unexpected Character")); //return ERROR token if not supported character
}
