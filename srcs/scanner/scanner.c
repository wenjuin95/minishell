/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:51:28 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/15 15:26:30 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* characters that when unquoted, separates words*/
#define METACHAR "|&;<>() \t\n"
#define OPERATOR "|&<>()"

/*
*	@brief create a token
*	@param type: token type
*	@param string: token value
*	@return token struct
*/
t_token	make_token(t_tok_type type, char *string)
{
	t_token	new_token;

	new_token.type = type;
	new_token.value = string;
	return (new_token);
}

/*
*	@brief scan the string for quotes
*	@param scanner: scanner struct
*	@param quote_type: type of quote
*	@return 0 if quote is found, -1 if quote is not found
*/
int	quotes(t_scanner *scanner, char quote_type)
{
	while (*scanner->current != '\0' && *scanner->current != quote_type) //current string no quote
		scanner->current++;
	if (*scanner->current == '\0' && *scanner->current != quote_type) //finsh the loop still not found quote
		return (-1);
	return (0);
}

/*
*	@brief create a word token
*	@param scanner: scanner struct
*	@return word token
*/
t_token	make_word_token(t_scanner *scanner)
{
	char	*word;
	char	c;

	scanner->current--; //move back to the last character for the word
	while (!ft_strchr(METACHAR, *scanner->current)) //if the current chat is not METACHAR
	{
		c = *(scanner->current++); //get the current character and move to the next
		if (c == '\'' || c == '"') //if the current character is ['] or ["]
		{
			if (quotes(scanner, c) == -1) //if the quote is not found
				return (make_token(TOK_ERROR, "Unclosed Quotes")); //return error token and error message
			scanner->current++; //move to the next character
		}
	}
	word = ft_substr(scanner->start, 0, (scanner->current - scanner->start)); //get only the word
	return (make_token(TOK_WORD, word)); //return the word token
}

/* 
*	@brief create an operator token
*	@param curr: current character
*	@param scanner: scanner struct
*	@note for single character operators it returns its type
*	@note for double character ones it checks it with match_next()
*	@note the function will not reach the last line 
*/
t_token	make_operator_token(char curr, t_scanner *scanner)
{
	if (curr == '(') //if is [ ( ]
		return (make_token(TOK_LPAREN, ft_strdup("("))); //return the token type and value
	if (curr == ')') 
		return (make_token(TOK_RPAREN, ft_strdup(")")));
	if (curr == '<') //if is [ < ]
		return (match_next('<', TOK_DLESS, TOK_LESS, scanner)); //check if the next character is [ < ]
	if (curr == '>')
		return (match_next('>', TOK_DGREAT, TOK_GREAT, scanner));
	if (curr == '|')
		return (match_next('|', TOK_OR_IF, TOK_PIPE, scanner));
	if (curr == '&')
		return (match_next('&', TOK_AND_IF, TOK_ERROR, scanner));
	return (make_token(TOK_ERROR, NULL));
}

/* 
*	@brief Scans the string and returns the next word/operator
*	@return a error token upon seeing a unsupported character 
*/
t_token	scan_token(t_scanner *scanner)
{
	char	curr;

	while (ft_isspace(*scanner->current)) //if the current character is a space
		scanner->current++;
	scanner->start = scanner->current; //set the start of the scanner to the current character
	if (*scanner->current == '\0') //if the current character is null
		return (make_token(TOK_EOF, NULL));
	curr = *scanner->current; //get the current character
	scanner->current++; //move to the next character
	if (ft_strchr(OPERATOR, curr)) //if the current character is an operator
		return (make_operator_token(curr, scanner)); 
	if (!ft_strchr(METACHAR, curr)) //if the current character is not METACHAR
		return (make_word_token(scanner));
	return (make_token(TOK_ERROR, "Unexpected Character")); 
}
