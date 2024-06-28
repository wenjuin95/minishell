/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_contructors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:52:03 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/26 17:41:27 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*exec_cmd(void)
{
	t_exec_cmd	*cmd;

	cmd = malloc(sizeof(t_exec_cmd));
	cmd->type = CMD_EXEC;
	cmd->argv = NULL;
	return ((t_cmd *)cmd);
}

t_cmd	*redir_cmd(char *filename, mode_t mode, int fd, t_cmd *next)
{
	t_redir_cmd	*cmd;

	cmd = malloc(sizeof(t_redir_cmd));
	cmd->type = CMD_REDIR;
	cmd->filename = filename;
	cmd->mode_flag = mode;
	cmd->fd = fd;
	cmd->next_cmd = next;
	return ((t_cmd *)cmd);
}

t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe_cmd	*cmd;

	cmd = malloc(sizeof(t_pipe_cmd));
	cmd->left_cmd = left;
	cmd->right_cmd = right;
	return ((t_cmd *)cmd);
}
