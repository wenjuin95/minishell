/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:44:56 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/11 17:32:34 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief save standard file descriptors
*	@param m_shell: minishell structure access to standard file descriptors
*/
void	save_std_fds(t_minishell *m_shell)
{
	m_shell->std_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	m_shell->std_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
	m_shell->std_fds[STDERR_FILENO] = dup(STDERR_FILENO);
}

/*
*	@brief reset standard file descriptors
*	@param m_shell: minishell structure access to standard file descriptors
*/
void	reset_std_fds(t_minishell *m_shell)
{
	dup2(m_shell->std_fds[STDIN_FILENO], STDIN_FILENO);
	dup2(m_shell->std_fds[STDOUT_FILENO], STDOUT_FILENO);
	dup2(m_shell->std_fds[STDERR_FILENO], STDERR_FILENO);
}
