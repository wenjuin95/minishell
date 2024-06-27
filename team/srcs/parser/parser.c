/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:39:34 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/27 13:30:18 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief	free token value if is word
*	@param	token :: struct token
*/
void	free_token(t_token token)
{
	if (token.type == TOK_WORD) //if token type is word
		free(token.value);
}

/*
*	@brief	print token
*	@param	line :: line to scan
*/
void	parse(const char *line)
{
	t_scanner	scanner;
	t_token		token;

	scanner = init_scanner(line); //initialize scanner
	while (1)
	{
		token = next_token(&scanner); //get next token
		print_token(token); //print token
		free_token(token); //free word token
		if (token.type == TOK_EOF) //if next token is end of file then break the loop
			break ;
	}
}
