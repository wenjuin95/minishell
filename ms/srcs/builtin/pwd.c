/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:10:04 by welow             #+#    #+#             */
/*   Updated: 2024/08/20 20:24:41 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	TODO:
*	1. pwd
*	2. pwd [any argument]
*/

/*
*	@brief	handle pwd command
*	@param	cmd argument to check
*	@param	m_shell get the exit code from m_shell
*	@return	0 if success, 1 if fail
*/
int	pwd_option(char **cmd, t_minishell *m_shell)
{
	int		i;
	char	*pwd;

	i = 1;
	if (cmd[i] == NULL)
	{
		pwd = NULL;
		pwd = getcwd(pwd, 0);
		printf("%s\n", pwd);
		free(pwd);
		m_shell->exit_code = EXIT_SUCCESS;
		return (m_shell->exit_code);
	}
	else
	{
		printf("pwd: %s: No such file or directory\n", cmd[i]);
		m_shell->exit_code = EXIT_FAILURE;
		return (m_shell->exit_code);
	}
}
