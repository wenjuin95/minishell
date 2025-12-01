/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:24:47 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/10/18 13:43:11 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief check the first token is redir, then add to redir_list
*	@param redir_list the redirection list
*	@param parser the parser struct
*	@note 1. if fail the parser status will stop the loop
*/
static void	parse_prefix(t_list **redir_list, t_parser *parser)
{
	while (tok_is_redirection(parser->next_token.type) && !parser->status)
	{
		add_to_redir_list(redir_list, parser);
	}
}

/*
*	@brief check the next token after the "parse_prefix" and check if is either
*		   word or redirect and then go to the argv_list or redir_list
*	@param argv_list the argv list
*	@param redir_list the redirection list
*	@param parser the parser struct
*	@note 1. in this loop if either argv_list or redir_list fail to parse
*		     then the loop will stop
*/
void	parse_suffix(t_list **argv_list,
						t_list **redir_list, t_parser *parser)
{
	while (parser->next_token.type == TOK_WORD
		|| tok_is_redirection(parser->next_token.type))
	{
		if (parser->next_token.type == TOK_WORD)
		{
			add_to_argv_list(argv_list, parser);
		}
		else
		{
			add_to_redir_list(redir_list, parser);
		}
		if (parser->status == FAIL)
			break ;
	}
}

/*
*	@brief parse the parenthesis and create a subshell node
*	@param parser the parser struct
*	@param m_shell get the exit_code
*	@return the subshell node
*	@note 1. print the error message and free here to prevent the
*			 token error print again in "parse" function
*/
t_cmd	*parse_parenthesis(t_parser *parser, t_minishell *m_shell)
{
	t_sub_cmd	*subshell;

	advance_psr(parser);
	subshell = malloc(sizeof(t_sub_cmd));
	subshell->type = CMD_SUBS;
	subshell->child = parse_cmd_list(parser, m_shell);
	if (parser->status == FAIL)
		return ((t_cmd *)subshell);
	if (parser->next_token.type != TOK_RPAREN)
	{
		ft_putendl_fd("Error unclosed quotes", STDERR_FILENO);
		parser->status = FAIL;
		m_shell->exit_code = GENERAL_ERROR;
		free_tree((t_cmd *)subshell);
		return (NULL);
	}
	advance_psr(parser);
	return ((t_cmd *)subshell);
}

/*
*	@brief get all the token to either argv_list or redir_list assign to cmd
*	@param parser the parser 
*	@return t_cmd* the command tree
*	@note 1. ft_lstclear(&argv_list, free) :: free here because when pass 
			 NULL the "parse" function will assume that the cmd_tree is NULL
*/
t_cmd	*parse_command(t_parser *parser, t_minishell *m_shell)
{
	t_cmd		*cmd;
	t_list		*argv_list;
	t_list		*redir_list;

	redir_list = NULL;
	argv_list = NULL;
	if (parser->next_token.type == TOK_LPAREN)
	{
		cmd = parse_parenthesis(parser, m_shell);
		return (cmd);
	}
	parse_prefix(&redir_list, parser);
	if (parser->next_token.type == TOK_WORD && !parser->status)
		add_to_argv_list(&argv_list, parser);
	if (!parser->status)
		parse_suffix(&argv_list, &redir_list, parser);
	if (!argv_list && !redir_list)
		parser->status = FAIL;
	if (parser->status == FAIL)
	{
		ft_lstclear(&argv_list, free);
		return (NULL);
	}
	cmd = exec_cmd(argv_list, redir_list);
	return ((t_cmd *)cmd);
}
