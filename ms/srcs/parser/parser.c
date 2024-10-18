/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:39:34 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/10/18 13:43:29 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief handle the token of "|"" and create a t_pipe_cmd node
*	@param parser the parser struct
*	@return t_cmd* the command tree as t_pipe_cmd
*	@note 1. check the first cmd is the error or not and parse the command result
*	@note 2. if the next token is "|", create a t_pipe_cmd node
*/
t_cmd	*parse_pipeline(t_parser *parser, t_minishell *m_shell)
{
	t_cmd		*cmd;
	t_pipe_cmd	*temp;

	cmd = parse_command(parser, m_shell);
	if (!cmd)
		return (NULL);
	while (parser->next_token.type == TOK_PIPE)
	{
		temp = malloc(sizeof(t_pipe_cmd));
		temp->type = CMD_PIPE;
		temp->left_cmd = cmd;
		advance_psr(parser);
		temp->right_cmd = parse_command(parser, m_shell);
		cmd = (t_cmd *)temp;
	}
	return (cmd);
}

/*
*	@brief handle the token of "||" and "&&" and create a t_list_cmd node
*	@param parser the parser struct
*	@return t_cmd* the command tree called t_list_cmd
*	@note 1. first cmd is check the left cmd and check is it a pipeline
*	@note 2. if the next token is "||" or "&&" then create a list command node
*/
t_cmd	*parse_cmd_list(t_parser *parser, t_minishell *m_shell)
{
	t_cmd		*cmd;
	t_list_cmd	*temp;

	cmd = parse_pipeline(parser, m_shell);
	if (!cmd)
		return (NULL);
	while (parser->next_token.type == TOK_OR_IF
		|| parser->next_token.type == TOK_AND_IF)
	{
		temp = malloc(sizeof(t_list_cmd));
		temp->type = CMD_LIST;
		temp->and_or = parser->next_token.type;
		temp->left_cmd = cmd;
		advance_psr(parser);
		temp->right_cmd = parse_pipeline(parser, m_shell);
		cmd = (t_cmd *)temp;
	}
	return (cmd);
}

/*
*	@brief Parse the input line and return the command tree
*	@param line the string to parse
*	@return if the token is EOF then t_cmd* the command tree
*	@return if not EOF then print syntax error and exit
*/
t_cmd	*parse(const char *line, t_minishell *m_shell)
{
	t_parser	parser;
	t_cmd		*cmd_tree;

	init_parser(&parser, line);
	cmd_tree = parse_cmd_list(&parser, m_shell);
	if (parser.next_token.type != TOK_EOF)
		parser.status = FAIL;
	if (parser.status == FAIL)
	{
		syntax_error(parser);
		if (cmd_tree)
			free_tree(cmd_tree);
		m_shell->exit_code = GENERAL_ERROR;
		return (NULL);
	}
	return (cmd_tree);
}
