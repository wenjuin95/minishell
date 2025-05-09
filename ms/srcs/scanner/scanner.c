/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:51:28 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/10/08 12:50:47 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* characters that when unquoted, separates words*/
#define METACHAR "|&;<>() \t\n"
#define OPERATOR "|&<>()"

/*
*	@brief give each of the string a type and assign to value
*	@param type token type
*	@param string the string
*	@return the token with its type and value
*/
t_token	make_token(t_tok_type type, char *string)
{
	t_token	new_token;

	new_token.type = type;
	new_token.value = string;
	return (new_token);
}

/*
*	@brief check the quote type
*	@param scanner the scanner struct
*	@param quote_type the quote type to check
*	@return 0 if is the quote type
*	@return , -1 if not the quote type
*/
int	quotes(t_scanner *scanner, char quote_type)
{
	while (*scanner->current != '\0' && *scanner->current != quote_type)
		scanner->current++;
	if (*scanner->current == '\0' && *scanner->current != quote_type)
		return (-1);
	return (0);
}

/*
*	@brief make a word token
*	@param scanner the scanner struct
*	@return if success the token with its type and value
*	@return if fail the error token upon seeing a unclosed quotes
*	@note 1. check the qutoe whether it is closed or not
*	@note 	 , if closed, then check word
*	@note 2. METACHAR is defined as "|&;<>() \t\n"
*/
t_token	make_word_token(t_scanner *scanner)
{
	char	*word;
	char	c;

	scanner->current--;
	while (!ft_strchr(METACHAR, *scanner->current))
	{
		c = *(scanner->current++);
		if (c == '\'' || c == '"')
		{
			if (quotes(scanner, c) == -1)
				return (make_token(TOK_ERROR, "Unclosed Quotes"));
			scanner->current++;
		}
	}
	word = ft_substr(scanner->start, 0, (scanner->current - scanner->start));
	return (make_token(TOK_WORD, word));
}

/*
*	@brief make token and check if the next character is the same
*	@param curr the current string
*	@param scanner the scanner struct 
*	@note 1. for single character operators it returns its type
*	@note 2. for double character ones it checks it with match_next()
*	@note 3. the function will not reach the last line 
*/
t_token	make_operator_token(char curr, t_scanner *scanner)
{
	if (curr == '(')
		return (make_token(TOK_LPAREN, to_gc_lst(ft_strdup("("))));
	if (curr == ')')
		return (make_token(TOK_RPAREN, to_gc_lst(ft_strdup(")"))));
	if (curr == '<')
		return (match_next('<', TOK_DLESS, TOK_LESS, scanner));
	if (curr == '>')
		return (match_next('>', TOK_DGREAT, TOK_GREAT, scanner));
	if (curr == '|')
		return (match_next('|', TOK_OR_IF, TOK_PIPE, scanner));
	if (curr == '&')
		return (match_next('&', TOK_AND_IF, TOK_ERROR, scanner));
	return (make_token(TOK_ERROR, NULL));
}

/* 
*	@brief Scans the string and returns the next word/operator(token)
*	@param scanner the scanner struct
*	@return if fail the error token upon seeing a unexpected character 
*	@return , if success the token with its type and value
*	@note 1. OPERATOR is defined as "|&<>()"
*	@note 2. METACHAR is defined as "|&;<>() \t\n"
*/
t_token	scan_token(t_scanner *scanner)
{
	char	curr;

	while (ft_isspace(*scanner->current))
		scanner->current++;
	scanner->start = scanner->current;
	if (*scanner->current == '\0')
		return (make_token(TOK_EOF, "newline"));
	curr = *scanner->current;
	scanner->current++;
	if (ft_strchr(OPERATOR, curr))
		return (make_operator_token(curr, scanner));
	if (!ft_strchr(METACHAR, curr))
		return (make_word_token(scanner));
	return (make_token(TOK_ERROR, NULL));
}
