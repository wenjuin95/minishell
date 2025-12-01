/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:13:46 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/14 21:29:03 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"
#include <math.h>

int	parse_expression(t_parser *parser);

int	parse_base(t_parser *parser)
{
	int	result;

	result = 0;
	if (parser->next_token.type == TOK_NUM)
	{
		result = parser->next_token.value;
		adv_parser(parser);
	}
	else if (parser->next_token.type == TOK_LPAREN)
	{
		adv_parser(parser);
		result = parse_expression(parser);
		if (parser->next_token.type != TOK_RPAREN)
			error_msg("Error! Expected closing ')'.");
		adv_parser(parser);
	}
	else if (parser->next_token.type == TOK_MINUS)
	{
		adv_parser(parser);
		result = -1 * parse_base(parser);
	}
	else
		error_msg("Syntax error or invalid character.");
	return (result);
}

int	parse_factor(t_parser *parser)
{
	int	result;
	int	exponent;

	result = parse_base(parser);
	while (parser->next_token.type == TOK_POWER)
	{
		adv_parser(parser);
		exponent = parse_factor(parser);
		result = pow(result, exponent);
	}
	return (result);
}

int	parse_term(t_parser *parser)
{
	int		result;
	t_ttype	next_tok_type;
	int		right_operand;

	result = parse_factor(parser);
	while (parser->next_token.type == TOK_STAR
		|| parser->next_token.type == TOK_SLASH)
	{
		next_tok_type = parser->next_token.type;
		adv_parser(parser);
		right_operand = parse_factor(parser);
		if (next_tok_type == TOK_STAR)
			result *= right_operand;
		else
		{
			if (right_operand == 0)
			{
				printf("Error! Dividing by Zero.\n");
				exit(1);
			}
			result /= right_operand;
		}
	}
	return (result);
}

int	parse_expression(t_parser *parser)
{
	int		result;
	t_ttype	next_tok_type;
	int		right_operand;

	result = parse_term(parser);
	while (parser->next_token.type == TOK_PLUS
		|| parser->next_token.type == TOK_MINUS)
	{
		next_tok_type = parser->next_token.type;
		adv_parser(parser);
		right_operand = parse_term(parser);
		if (next_tok_type == TOK_PLUS)
			result += right_operand;
		else
			result -= right_operand;
	}
	return (result);
}

void	parser(const char *input)
{
	t_parser	parser;
	int			result;

	init_parser(&parser, input);
	result = parse_expression(&parser);
	if (parser.next_token.type != TOK_EOF)
	{
		printf("Syntax Error.\n");
		exit(1);
	}
	printf("Result: %d\n", result);
}
