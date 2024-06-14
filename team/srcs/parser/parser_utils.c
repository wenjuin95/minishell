/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:05:56 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/05/22 21:45:16 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token token)
{
	printf("%2d ", token.type);
	if (token.type == TOK_EOF)
		printf("EOF\n");
	else
		printf("'%s'\n", token.value);
}
