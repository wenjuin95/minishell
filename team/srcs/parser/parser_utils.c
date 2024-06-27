/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:05:56 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/27 19:40:57 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*get_type(t_ttype type)
{
	if (type == TOK_WORD)
		return ("TOK_WORD  ");
	else if (type == TOK_PIPE)
		return ("TOK_PIPE  ");
	else if (type == TOK_LESS)
		return ("TOK_LESS  ");
	else if (type == TOK_GREAT)
		return ("TOK_GREAT ");
	else if (type == TOK_DLESS)
		return ("TOK_DLESS ");
	else if (type == TOK_DGREAT)
		return ("TOK_DGREAT");
	else if (type == TOK_OR_IF)
		return ("TOK_OR_IF ");
	else if (type == TOK_AND_IF)
		return ("TOK_AND_IF");
	else if (type == TOK_LPAREN)
		return ("TOK_LPAREN");
	else if (type == TOK_RPAREN)
		return ("TOK_RPAREN");
	else if (type == TOK_EOF)
		return ("TOK_EOF   ");
	else
		return ("TOK_ERROR ");
}

/*
*	@brief	print token
*	@param	token :: struct token
*/
void	print_token(t_token token)
{
	const char *_type = get_type(token.type); //get token type
	printf("\033[0;35mTYPE\033[0m-> %s ", _type); //print token type
	if (token.type == TOK_EOF) //if token type is end of file
		printf("\033[0;35mVALUE\033[0m->  EOF\n");
	else
		printf("\033[0;35mVALUE\033[0m-> '%s'\n", token.value); //continue print token value
}
