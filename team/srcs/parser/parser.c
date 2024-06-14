/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:39:34 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/05/22 16:27:46 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token token)
{
	if (token.type == TOK_WORD)
		free(token.value);
}

void	parse(const char *line)
{
	t_scanner	scanner;
	t_token		token;

	scanner = init_scanner(line);
	while (1)
	{
		token = next_token(&scanner);
		print_token(token);
		free_token(token);
		if (token.type == TOK_EOF)
			break ;
	}
}
