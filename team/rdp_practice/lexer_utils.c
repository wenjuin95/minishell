/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:53:37 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/13 13:01:22 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

#define OPERATORS "+-*/^()"

char	advance(t_lexer *lexer)
{
	lexer->curr++;
	return (*(lexer->curr -1));
}

void	init_lexer(t_lexer *lexer, const char *input)
{
	lexer->start = input;
	lexer->curr = input;
}

t_token	num_token(t_lexer *lexer)
{
	t_token	token;
	char	*num_str;

	while (ft_isdigit(*lexer->curr))
		advance(lexer);
	num_str = ft_substr(lexer->start, 0, (lexer->curr - lexer->start));
	token.type = TOK_NUM;
	token.value = ft_atoi(num_str);
	free(num_str);
	return (token);
}

t_token	op_token(char operator)
{
	if (operator == '+')
		return ((t_token){TOK_PLUS, 0});
	else if (operator == '-')
		return ((t_token){TOK_MINUS, 0});
	else if (operator == '*')
		return ((t_token){TOK_STAR, 0});
	else if (operator == '/')
		return ((t_token){TOK_SLASH, 0});
	else if (operator == '^')
		return ((t_token){TOK_POWER, 0});
	else if (operator == '(')
		return ((t_token){TOK_LPAREN, 0});
	else if (operator == ')')
		return ((t_token){TOK_RPAREN, 0});
	else
		return ((t_token){TOK_ERR, 0});
}

t_token	next_token(t_lexer *lexer)
{
	char	c;

	while (*lexer->curr == ' ')
		advance(lexer);
	lexer->start = lexer->curr;
	if (*lexer->curr == '\0')
		return ((t_token){TOK_EOF, 0});
	c = advance(lexer);
	if (ft_isdigit(c))
		return (num_token(lexer));
	if (ft_strchr(OPERATORS, c))
		return (op_token(c));
	return ((t_token){TOK_ERR, 0});
}
