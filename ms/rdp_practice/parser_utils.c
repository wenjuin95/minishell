/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:15:03 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/13 16:42:12 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

void	init_parser(t_parser *parser, const char *input)
{
	init_lexer(&parser->lexer, input);
	parser->next_token = next_token(&parser->lexer);
}

void	adv_parser(t_parser *parser)
{
	parser->next_token = next_token(&parser->lexer);
}
