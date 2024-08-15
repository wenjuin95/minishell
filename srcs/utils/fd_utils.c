/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:44:56 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/08/12 14:56:27 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief save the standard file descriptors to the minishell struct
*/
void	save_std_fds(t_minishell *m_shell)
{
	m_shell->std_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	m_shell->std_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
	m_shell->std_fds[STDERR_FILENO] = dup(STDERR_FILENO);
}

/*
*	@brief reset the standard file descriptors with the saved file descriptor
*/
void	reset_std_fds(t_minishell *m_shell)
{
	dup2(m_shell->std_fds[STDIN_FILENO], STDIN_FILENO);
	dup2(m_shell->std_fds[STDOUT_FILENO], STDOUT_FILENO);
	dup2(m_shell->std_fds[STDERR_FILENO], STDERR_FILENO);
}
