/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_contructors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:52:03 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/08 15:49:35 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief create an execution command node
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
*	@brief create a redirection command node
*	@param redir_lst: redirections linked list
*	@param next: next command node
*	@note redir_list is the content of the node
*	@note next is the next node
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
*	@brief create a pipe command node
*	@param left: left command node
*	@param right: right command node
*/
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe_cmd	*cmd;

	cmd = malloc(sizeof(t_pipe_cmd));
	cmd->left_cmd = left;
	cmd->right_cmd = right;
	return ((t_cmd *)cmd);
}
