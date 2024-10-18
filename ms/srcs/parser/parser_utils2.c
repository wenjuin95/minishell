/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:52:03 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/10/18 12:48:41 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief create a exec command node
*	@param argv the argv list
*	@param redir the redir list
*	@return t_cmd* the command tree
*/
t_cmd	*exec_cmd(t_list *argv, t_list *redir)
{
	t_exec_cmd	*cmd;

	cmd = malloc(sizeof(t_exec_cmd));
	if (!cmd)
		return (NULL);
	cmd->type = CMD_EXEC;
	cmd->argv_list = argv;
	cmd->redir_list = redir;
	return ((t_cmd *)cmd);
}

/*
*	@brief create a pipe command node
*	@param left the left command
*	@param right the right command
*	@return t_cmd* the command tree
*/
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe_cmd	*cmd;

	cmd = malloc(sizeof(t_pipe_cmd));
	if (!cmd)
		return (NULL);
	cmd->left_cmd = left;
	cmd->right_cmd = right;
	return ((t_cmd *)cmd);
}

/*
*	@brief print the syntax error message
*	@param parser the parser struct
*/
void	syntax_error(t_parser parser)
{
	if (parser.next_token.type == TOK_ERROR)
		ft_putendl_fd("unexpected character", STDERR_FILENO);
	else
	{
		ft_putstr_fd("Syntax error near ", STDERR_FILENO);
		ft_putendl_fd(parser.next_token.value, STDERR_FILENO);
	}
	if (parser.next_token.type != TOK_EOF)
		free(parser.next_token.value);
}
