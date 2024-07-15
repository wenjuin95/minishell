/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:39:34 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/11 17:23:55 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief rediction before the command
	type and value to the redirection linked list
*	@param redir_list: redirection linked list
*	@param parser: parser
*/
void	parse_prefix(t_list **redir_list, t_parser *parser)
{
	while (tok_is_redirection(parser->next_token.type))
	{
		add_to_redir_list(redir_list, parser);
	}
}

/*
*	@brief rediction after the command
*	@param arr: dynamic array
*	@param redir_list: redirection linked list
*	@param parser: parser
*/
void	parse_suffix(t_dym_arr *arr, t_list **redir_list, t_parser *parser)
{
	while (parser->next_token.type == TOK_WORD
		|| tok_is_redirection(parser->next_token.type))
	{
		if (parser->next_token.type == TOK_WORD)
		{
			add_to_array(arr, parser->next_token.value);
			advance_psr(parser);
		}
		else
		{
			add_to_redir_list(redir_list, parser);
		}
	}
}

/*
*	@brief parse the command
*	@param parser: parser
*	@return command node
*/
t_cmd	*parse_command(t_parser *parser)
{
	t_cmd		*cmd;
	t_dym_arr	*argv_dym;
	t_list		*redir_list;

	redir_list = NULL;
	argv_dym = dym_arr_init();
	parse_prefix(&redir_list, parser);
	if (parser->next_token.type == TOK_WORD)
	{
		add_to_array(argv_dym, parser->next_token.value);
		advance_psr(parser);
	}
	parse_suffix(argv_dym, &redir_list, parser);
	add_to_array(argv_dym, NULL);
	cmd = exec_cmd(argv_dym->arr, redir_list);
	free(argv_dym);
	return ((t_cmd *)cmd);
}

/*
*	@brief parse the pipeline
*	@param parser: parser
*	@return command node
*/
t_cmd	*parse_pipeline(t_parser *parser)
{
	t_cmd		*cmd;
	t_pipe_cmd	*temp;

	cmd = parse_command(parser);
	while (parser->next_token.type == TOK_PIPE)
	{
		temp = malloc(sizeof(t_pipe_cmd));
		temp->type = CMD_PIPE;
		temp->left_cmd = cmd;
		advance_psr(parser);
		temp->right_cmd = parse_command(parser);
		cmd = (t_cmd *)temp;
	}
	return (cmd);
}

/*
*	@brief initialize the parser
*	@param line: line to parse
*/
t_cmd	*parse(const char *line)
{
	t_parser	parser;
	t_cmd		*cmd_tree;

	init_parser(&parser, line);
	cmd_tree = parse_pipeline(&parser);
	return (cmd_tree);
}
