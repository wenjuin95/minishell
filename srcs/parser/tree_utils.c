/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:25:30 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/10/10 21:32:18 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst(t_cmd *node)
{
	t_list_cmd	*lcmd;

	lcmd = (t_list_cmd *)node;
	free_tree(lcmd->left_cmd);
	free_tree(lcmd->right_cmd);
}

void	free_subs(t_cmd	*node)
{
	t_sub_cmd	*scmd;

	scmd = (t_sub_cmd *)node;
	free_tree(scmd->child);
}

void	free_tree(t_cmd *node)
{
	t_exec_cmd	*ecmd;
	t_pipe_cmd	*pcmd;

	if (node == NULL)
		return ;
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
	else if (node->type == CMD_LIST)
		free_lst(node);
	else if (node->type == CMD_SUBS)
		free_subs(node);
	free(node);
}
