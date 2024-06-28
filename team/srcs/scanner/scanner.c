/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:51:28 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/21 21:04:12 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* characters that when unquoted, separates words*/
#define METACHAR "|&;<>() \t\n"
#define OPERATOR "|&<>()"

t_token	make_token(t_ttype type, char *string)
{
	t_token	new_token;

	new_token.type = type;
	new_token.value = string;
	return (new_token);
}

int	quotes(t_scanner *scanner, char quote_type)
{
	while (*scanner->current != '\0' && *scanner->current != quote_type)
		scanner->current++;
	if (*scanner->current == '\0' && *scanner->current != quote_type)
		return (-1);
	return (0);
}

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
				return (make_token(TOK_ERROR, "Unclosed quotes"));
			scanner->current++;
		}
	}
	word = ft_substr(scanner->start, 0, (scanner->current - scanner->start));
	return (make_token(TOK_WORD, word));
}

/* 
for single character operators it returns its type
for double character ones it checks it with match_next()
Notes: the function will not reach the last line 
*/
t_token	make_operator_token(char curr, t_scanner *scanner)
{
	if (curr == '(')
		return (make_token(TOK_LPAREN, NULL));
	if (curr == ')')
		return (make_token(TOK_RPAREN, NULL));
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
Scans the string and returns the next word/operator
Returns a error token upon seeing a unsupported character 
*/
t_token	scan_token(t_scanner *scanner)
{
	char	curr;

	while (ft_isspace(*scanner->current))
		scanner->current++;
	scanner->start = scanner->current;
	if (*scanner->current == '\0')
		return (make_token(TOK_EOF, NULL));
	curr = *scanner->current;
	scanner->current++;
	if (ft_strchr(OPERATOR, curr))
		return (make_operator_token(curr, scanner));
	if (!ft_strchr(METACHAR, curr))
		return (make_word_token(scanner));
	return (make_token(TOK_ERROR, "Unexpected Character"));
}
