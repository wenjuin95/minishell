/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:39:34 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/08/16 19:48:19 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief check if the token is redirection then go to the "add_to_redir_list"
*	@param redir_list the redirection list
*	@param parser the parser struct
*	@note 1. loop through and check is ("<", ">", "<<", ">>")
*/
void	parse_prefix(t_list **redir_list, t_parser *parser)
{
	while (tok_is_redirection(parser->next_token.type))
	{
		print_token(parser->next_token); //debug
		add_to_redir_list(redir_list, parser);
	}
}

/*
*	@brief check if the token is word then go to the "add_to_argv_list"
*	@bref check if the token is redirection then go to the "add_to_redir_list"
*	@param argv_list the argv list
*	@param redir_list the redirection list
*	@param parser the parser struct
*	@note 1. loop through the next token until not a word or redirection
*/
void	parse_suffix(t_list **argv_list, t_list **redir_list, t_parser *parser)
{
	while (parser->next_token.type == TOK_WORD
		|| tok_is_redirection(parser->next_token.type))
	{
		if (parser->next_token.type == TOK_WORD)
		{
			print_token(parser->next_token); //debug
			add_to_argv_list(argv_list, parser);
		}
		else
		{
			print_token(parser->next_token); //debug
			add_to_redir_list(redir_list, parser);
		}
	}
}

/*
*	@brief get all the token to either argv_list or redir_list assign to cmd
*	@param parser the parser struct
*	@return t_cmd* the command tree
*/
t_cmd	*parse_command(t_parser *parser)
{
	t_cmd		*cmd;
	t_list		*argv_list;
	t_list		*redir_list;

	redir_list = NULL;
	argv_list = NULL;
	parse_prefix(&redir_list, parser);
	if (parser->next_token.type == TOK_WORD)
	{
		print_token(parser->next_token); //debug
		add_to_argv_list(&argv_list, parser);
	}
	parse_suffix(&argv_list, &redir_list, parser);
	cmd = exec_cmd(argv_list, redir_list);
	print_token(parser->next_token); //debug
	return ((t_cmd *)cmd);
}

/*
*	@brief in the parse_command if founnd pipe, create a pipe command node
*	@param parser the parser struct
*	@return t_cmd* the command tree
*	@note 1. first cmd is the left command
*	@note 2. after the pipe token, the next token is the right command
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
*	@brief Parse the input line and return the command tree
*	@param line the string to parse
*	@return if the token is EOF then t_cmd* the command tree
*	@return if not EOF then print syntax error and exit
*/
t_cmd	*parse(const char *line)
{
	t_parser	parser;
	t_cmd		*cmd_tree;

	init_parser(&parser, line);
	cmd_tree = parse_pipeline(&parser);
	if (parser.next_token.type != TOK_EOF)
	{
		ft_putendl_fd("Syntax Error.", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (cmd_tree);
}
