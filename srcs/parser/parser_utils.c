/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:05:56 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/10/19 23:17:17 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief scan the cmd and assign each of the token type
*	@param parser the parser struct
*	@param line the string to be scanned
*/
void	init_parser(t_parser *parser, const char *line)
{
	init_scanner(&parser->scanner, line);
	parser->next_token = scan_token(&parser->scanner);
	parser->status = SUCCESS;
}

/*
*	@brief to get the next token
*	@param parser the parser struct
*	@note 1. free the current token if it is not EOF
*	@note 2. get the next token for the right command
*	@note 3. if the next token is error, print the error and exit
*/
void	advance_psr(t_parser *parser)
{
	if (parser->next_token.type != TOK_EOF)
		free(parser->next_token.value);
	parser->next_token = scan_token(&parser->scanner);
}

/*
*	@brief check if the token is redirection
*	@param type the token type
*	@return depend on the type (">", "<", ">>", "<<")
*/
bool	tok_is_redirection(t_tok_type type)
{
	return (type == TOK_GREAT || type == TOK_LESS || type == TOK_DGREAT
		|| type == TOK_DLESS);
}

/*
*	@brief add "WORD" token to argv list
*	@param argv_list the argv list
*	@param parser the parser struct
*	@note 1. if any error or null when add node to the list, 
		  set the status to FAIL
*	@note 2. advance_psr to get the next token/word
*/
void	add_to_argv_list(t_list **argv_list, t_parser *parser)
{
	char	*new_argv;
	t_list	*new_node;

	new_argv = to_gc_lst(ft_strdup(parser->next_token.value));
	new_node = ft_lstnew(new_argv);
	ft_lstadd_back(argv_list, new_node);
	advance_psr(parser);
}

/*
*	@brief add "WORD" token from after "REDIR" token to redirection list
*	@param redir_list the redirection list
*	@param parser the parser struct
*	@note 1. "advance_psr" to get the next token after "REDIR" token
*	@note 1. if the next token after "redir" token is not "WORD" then
*		  free the new_data, print error and set the status to FAIL
*/
void	add_to_redir_list(t_list **redir_list, t_parser *parser)
{
	t_redir_data	*new_data;

	new_data = malloc(sizeof(t_redir_data));
	new_data->type = parser->next_token.type;
	advance_psr(parser);
	if (parser->next_token.type == TOK_WORD)
	{
		new_data->value = ft_strdup(parser->next_token.value);
		to_gc_lst(new_data->value);
		ft_lstadd_back(redir_list, ft_lstnew((void *)new_data));
		advance_psr(parser);
	}
	else
	{
		parser->status = FAIL;
		free(new_data);
	}
}
