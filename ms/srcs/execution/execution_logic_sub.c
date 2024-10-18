/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_logic_sub.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:12:12 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/10/10 21:57:07 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Logical Operators
 * cmd1 || cmd2 (Or) - Only execute cmd2 if cmd1 fail (exit code not 0)
 * cmd1 && cmd2 (And) - Only execute cmd2 if cmd1 success (exit code 0)
 * Based on a concept called short-curcuit evaulation
 * when evaluating 'or' if first case is true then we can skip running 2nd case
 */
void	command_list(t_cmd *cmd, t_minishell *m_shell)
{
	t_list_cmd	*lst_cmd;

	lst_cmd = (t_list_cmd *)cmd;
	eval_tree(lst_cmd->left_cmd, m_shell);
	if (lst_cmd->and_or == TOK_AND_IF && m_shell->exit_code == 0)
		eval_tree(lst_cmd->right_cmd, m_shell);
	if (lst_cmd->and_or == TOK_OR_IF && m_shell->exit_code != 0)
		eval_tree(lst_cmd->right_cmd, m_shell);
}

void	command_subshell(t_cmd *cmd, t_minishell *m_shell)
{
	t_sub_cmd	*sub_cmd;

	sub_cmd = (t_sub_cmd *)cmd;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	m_shell->pid = fork();
	if (m_shell->pid == 0)
	{
		eval_tree(sub_cmd->child, m_shell);
		exit(m_shell->exit_code);
	}
	waitpid(m_shell->pid, &m_shell->status, 0);
	get_exit_code(m_shell);
}
