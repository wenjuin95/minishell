/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:14:27 by welow             #+#    #+#             */
/*   Updated: 2024/06/27 19:45:31 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_input(char *cmd)
{
	if (cmd == NULL)
		return (true);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (true);
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (true);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (true);
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (true);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return (true);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (true);
	return (false);
}

/*
*	@brief Check the input is builtin or not
*	@param cmd :: The command to check
*	@param env_list :: The env list
*/
void	execute_input(t_minishell *m_shell, char **cmd)
{
	if (*cmd == NULL)
		return ;
	if (ft_strncmp(*cmd, "env", 3) == 0)
	{
		ft_printf("\033[1;31mBUILT-IN: ENV:\033[0m\n"); //debug
		env_option(m_shell, cmd);
	}
	if (ft_strncmp(*cmd, "echo", 4) == 0)
	{
		ft_printf("\033[1;31mBUILT-IN: ECHO:\033[0m\n"); //debug
		echo_option(cmd);
	}
	if (ft_strncmp(*cmd, "pwd", 3) == 0)
	{
		ft_printf("\033[1;31mBUILT-IN: PWD:\033[0m\n"); //debug
		pwd_option(cmd);
	}
	if (ft_strncmp(*cmd, "export", 6) == 0)
	{
		ft_printf("\033[1;31mBUILT-IN: EXPORT:\033[0m\n"); //debug
		export_option(m_shell, cmd);
	}
	if (ft_strncmp(*cmd, "unset", 5) == 0)
	{
		ft_printf("\033[1;31mBUILT-IN: UNSET\033[0m\n"); //debug
		unset_option(m_shell, cmd);
	}
	if (ft_strncmp(*cmd, "exit", 5) == 0)
	{
		ft_printf("\033[1;31mBUILT-IN: EXIT\033[0m\n"); //debug
		exit_option(m_shell, cmd);
	}
	if (ft_strncmp(*cmd, "cd", 2) == 0)
	{
		ft_printf("\033[1;31mBUILT-IN: CD\033[0m\n"); //debug
		cd_option(m_shell, cmd);
	}
}
