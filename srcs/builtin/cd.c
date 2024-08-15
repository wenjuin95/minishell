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
solve this:
cd
cd /
cd -
exit
*/

/*
*	@brief get value from env_lst with the name (for modify)
*	@param name name of the value you lookinng for
*	@param m_shell get env link list from m_shell
*	@return value of the environment variable you looking for
*/
char	*get_envlst_value(char *name, t_minishell *m_shell)
{
	t_env_lst	*current;

	current = m_shell->env_lst;
	while (current)
	{
		if (ft_strncmp(name, current->name, ft_strlen(name)) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

/*
*	@brief update PWD to the current directory
*	@param m_shell get env link list and exit code from m_shell
*	@return 0 if success update pwd, 1 if failed
*/
static int	chg_pwd(t_minishell *m_shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	update_env("PWD", pwd, false, m_shell);
	free(pwd);
	return (0);
}

/*
*	@brief change to main directory
*	@param m_shell get env link list and exit code from m_shell
*	@return 0 if success update pwd, 1 if failed print error
*/
static int	main_dir(t_minishell *m_shell)
{
	char	*home;
	char	*oldpwd;

	oldpwd = get_envlst_value("OLDPWD", m_shell);
	if (oldpwd != NULL)
		update_env("OLDPWD", get_envlst_value("PWD", m_shell), false, m_shell);
	else
		update_env("OLDPWD", get_envlst_value("PWD", m_shell), true, m_shell);
	home = get_envlst_value("HOME", m_shell);
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
*	@param m_shell get env link list and exit code from m_shell
*	@return 0 if success update pwd, 1 if failed print error
*/
static int	return_dir(t_minishell *m_shell)
{
	if (get_envlst_value("OLDPWD", m_shell) == NULL
		|| chdir(get_envlst_value("OLDPWD", m_shell)) == -1)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	if (chdir(get_envlst_value("OLDPWD", m_shell)) == 0)
	{
		update_env("PWD", get_envlst_value("OLDPWD", m_shell), false, m_shell);
		return (0);
	}
	return (1);
}

/*
*	@brief handle cd command
*	@param cmd argument to check
*	@param m_shell get env link list and exit code from m_shell
*	@return 0 if success chg directory, 1 if failed print error
*/
int	cd_option(char **cmd, t_minishell *m_shell)
{
	int	i;

	i = 1;
	if (cmd[i] == NULL || cmd[i][0] == '~')
	{
		m_shell->exit_code = main_dir(m_shell);
		return (m_shell->exit_code);
	}
	if (cmd[i][0] == '-')
		return (return_dir(m_shell));
	if (chdir(cmd[i]) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", cmd[i]);
		m_shell->exit_code = 1;
		return (m_shell->exit_code);
	}
	update_env("OLDPWD", get_envlst_value("PWD", m_shell), false, m_shell);
	m_shell->exit_code = chg_pwd(m_shell);
	return (m_shell->exit_code);
}
