/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:14:27 by welow             #+#    #+#             */
/*   Updated: 2024/07/09 13:56:56 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_input(char *cmd)
{
	if (cmd == NULL)
		return (true);
	if (ft_strncmp(cmd, "env", 3) == 0 && (ft_strlen(cmd) == 3))
		return (true);
	if (ft_strncmp(cmd, "echo", 4) == 0 && (ft_strlen(cmd) == 4))
		return (true);
	if (ft_strncmp(cmd, "pwd", 3) == 0 && (ft_strlen(cmd) == 3))
		return (true);
	if (ft_strncmp(cmd, "export", 6) == 0 && (ft_strlen(cmd) == 6))
		return (true);
	if (ft_strncmp(cmd, "unset", 5) == 0 && (ft_strlen(cmd) == 5))
		return (true);
	if (ft_strncmp(cmd, "exit", 4) == 0 && (ft_strlen(cmd) == 4))
		return (true);
	if (ft_strncmp(cmd, "cd", 2) == 0 && (ft_strlen(cmd) == 2))
		return (true);
	return (false);
}

/*
*	@brief Check the input is builtin or not
*	@param cmd :: The command to check
*	@param m_shell :: access to the minishell struct
*/
void	execute_input(t_minishell *m_shell, char **cmd)
{
	if (*cmd == NULL)
		return ;
	if (ft_strncmp(*cmd, "env", 3) == 0)
		env_option(m_shell, cmd);
	if (ft_strncmp(*cmd, "echo", 4) == 0)
		echo_option(cmd);
	if (ft_strncmp(*cmd, "pwd", 3) == 0)
		pwd_option(cmd);
	if (ft_strncmp(*cmd, "export", 6) == 0)
		export_option(m_shell, cmd);
	if (ft_strncmp(*cmd, "unset", 5) == 0)
		unset_option(m_shell, cmd);
	if (ft_strncmp(*cmd, "exit", 5) == 0)
		exit_option(m_shell, cmd);
	if (ft_strncmp(*cmd, "cd", 2) == 0)
		cd_option(m_shell, cmd);
}
