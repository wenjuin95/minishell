/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:59:45 by welow             #+#    #+#             */
/*   Updated: 2024/05/27 13:59:45 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	TODO:
*	1. cd
*	2. cd [any argument]
*/

/*
*	@brief update PWD to the current directory
*/
static int	chg_pwd(t_minishell *m_shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	update_env("PWD", pwd, false, m_shell);
	return (0);
}

/*
*	@brief change to main directory
*/
static int	main_dir(t_minishell *m_shell)
{
	char	*home;

	update_env("OLDPWD", getenv("PWD"),
		false, m_shell);
	home = getenv("HOME");
	if (home == NULL)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(home) == 0)
	{
		update_env("PWD", home, false, m_shell);
		return (0);
	}
	return (1);
}

/*
*	@brief change to the previous directory
*/
static int	return_dir(t_minishell *m_shell)
{
	if (getenv("OLDPWD") == NULL)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	if (chdir(getenv("OLDPWD")) == 0)
	{
		update_env("PWD", getenv("OLDPWD"),
			false, m_shell);
		return (0);
	}
	return (1);
}

int	cd_option(t_minishell *m_shell, char **cmd)
{
	int	i;

	i = 1;
	if (cmd[i] == NULL || cmd[i][0] == '~')
		return (main_dir(m_shell));
	if (cmd[i][0] == '-')
		return (return_dir(m_shell));
	if (chdir(cmd[i]) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", cmd[i]);
		return (1);
	}
	update_env("OLDPWD", getenv("PWD"),
		false, m_shell);
	return (chg_pwd(m_shell));
}

