/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:05:56 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/27 13:31:14 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief	print token
*	@param	token :: struct token
*/
void	print_token(t_token token)
{
	printf("%2d ", token.type); //print token type
	if (token.type == TOK_EOF) //if token type is end of file
		printf("EOF\n");
	else
		printf("'%s'\n", token.value); //continue print token value
}
