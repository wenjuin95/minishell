/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:25:30 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/08/05 13:29:09 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree(t_cmd *node)
{
	t_exec_cmd	*ecmd;
	t_pipe_cmd	*pcmd;

	if (node->type == CMD_EXEC)
	{
		ecmd = (t_exec_cmd *)node;
		ft_lstclear(&ecmd->argv_list, free);
		ft_lstclear(&ecmd->redir_list, free);
	}
	else if (node->type == CMD_PIPE)
	{
		pcmd = (t_pipe_cmd *)node;
		free_tree(pcmd->left_cmd);
		free_tree(pcmd->right_cmd);
	}
	free(node);
}
