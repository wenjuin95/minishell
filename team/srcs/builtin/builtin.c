/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:14:27 by welow             #+#    #+#             */
/*   Updated: 2024/06/17 16:55:35 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief Check the input is builtin or not
*	@param cmd :: The command to check
*	@param env_list :: The env list
*/
void	check_input(char **cmd, t_minishell m_shell)
{
	if (*cmd == NULL)
		return ;
	if (ft_strncmp(*cmd, "env", 3) == 0) //if "env" execute env
		env_option(m_shell.env_list, cmd);
	if (ft_strncmp(*cmd, "echo", 4) == 0) //if "echo" execute echo
		echo_option(cmd);
	if (ft_strncmp(*cmd, "pwd", 3) == 0) //if "pwd" execute pwd
		pwd_option(cmd);
	if (ft_strncmp(*cmd, "export", 6) == 0) //if "export" execute export
		export_option(m_shell.env_list, cmd);
	if (ft_strncmp(*cmd, "unset", 5) == 0) //if "unset" execute unset
		unset_option(m_shell.env_list, cmd);
	if (ft_strncmp(*cmd, "cd", 2) == 0) //if "cd" execute cd
		cd_option(m_shell.env_list, cmd);
	if (ft_strncmp(*cmd, "exit", 5) == 0) //if "exit" execute exit
		exit_option(m_shell, cmd);
}