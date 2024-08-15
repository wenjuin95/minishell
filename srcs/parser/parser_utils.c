/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:05:56 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/08/12 14:13:25 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief scan the string and get thier token & value, store in parser
*	@param parser the parser struct
*	@param line the string to be scanned
*/
void	init_parser(t_parser *parser, const char *line)
{
	init_scanner(&parser->scanner, line);
	parser->next_token = scan_token(&parser->scanner);
}

/*
*	@brief check the next token and store in next_token to parser
*	@param parser the parser struct
*	@note 1. free the next_token value if not EOF
* 	@note 2. assign the next_token to the next token if is EOF
*	@note 3. if the next_token is error, print the error and exit
*/
void	advance_psr(t_parser *parser)
{
	if (parser->next_token.type != TOK_EOF)
		free(parser->next_token.value);
	parser->next_token = scan_token(&parser->scanner);
	if (parser->next_token.type == TOK_ERROR)
	{
		ft_putendl_fd(parser->next_token.value, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
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
*	@brief add word to argv list
*	@param argv_list the argv list
*	@param parser the parser struct
*	@note 1. advance_psr to get the next token/word
*/
void	add_to_argv_list(t_list **argv_list, t_parser *parser)
{
	char	*new_argv;

	new_argv = ft_strdup(parser->next_token.value);
	ft_lstadd_back(argv_list, ft_lstnew(new_argv));
	advance_psr(parser);
}

/*
*	@brief check if is word then add to redirection list
*	@param redir_list the redirection list
*	@param parser the parser struct
*	@note 1. advance_psr to get the next token/word
*	@note 2. if the next token is word, add to redirection list
*	@note 3. if is not print syntax error
*/
void	add_to_redir_list(t_list **redir_list, t_parser *parser)
{
	t_redir_data	*new_data;

	new_data = malloc(sizeof(t_redir_data));
	new_data->type = parser->next_token.type;
	advance_psr(parser);
	if (parser->next_token.type == TOK_WORD)
	{
		new_data->value = to_gc_lst(ft_strdup(parser->next_token.value));
		ft_lstadd_back(redir_list, ft_lstnew((void *)new_data));
		advance_psr(parser);
	}
	else
		printf("Syntax Error near %s\n", parser->next_token.value);
}

/* FOR DEBUG */

/* void	print_token(t_token token)
{
	printf("%2d ", token.type);
	if (token.type == TOK_EOF)
		printf("EOF\n");
	else
		printf("'%s'\n", token.value);
} */