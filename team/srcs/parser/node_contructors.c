/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_contructors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:52:03 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/02 12:16:19 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief Create an execution command node
*	@return t_cmd* New command node
*	@note node contain command type and argv set to NULL
*/
t_cmd	*exec_cmd(void)
{
	t_exec_cmd	*cmd;

	cmd = malloc(sizeof(t_exec_cmd));
	cmd->type = CMD_EXEC;
	cmd->argv = NULL;
	return ((t_cmd *)cmd);
}

/*
*	@brief Create a redirection command node
*	@param redir_lst List of redirections
*	@param next Next command
*	@return t_cmd* New command node
*	@note node contain command type, redir_list and next command
*/
t_cmd	*redir_cmd(t_list *redir_lst, t_cmd *next)
{
	t_redir_cmd	*cmd;

	cmd = malloc(sizeof(t_redir_cmd));
	cmd->type = CMD_REDIR;
	cmd->redir_list = redir_lst;
	cmd->next_cmd = next;
	return ((t_cmd *)cmd);
}

/*
*	@brief Create a pipe command node
*	@param left Left command
*	@param right Right command
*	@return t_cmd* New command node
*	@note node contain command type, left and right command
*/
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe_cmd	*cmd;

	cmd = malloc(sizeof(t_pipe_cmd));
	cmd->left_cmd = left;
	cmd->right_cmd = right;
	return ((t_cmd *)cmd);
}
