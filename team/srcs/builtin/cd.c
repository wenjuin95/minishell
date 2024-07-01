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

// /*
// *	@brief get value from env_lst with the name (for modify)
// *	@param name name of the value you lookinng for
// *	@return value of the environment variable you looking for
// */
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
solve this:
cd
cd /
cd -
exit
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
	update_env("PWD", pwd, false, m_shell); //update PWD
	free(pwd);
	return (0);
}

/*
*	@brief change to main directory
*	@return 0 if success update pwd, 1 if failed print error
*/
static int	main_dir(t_minishell *m_shell)
{
	char	*home;

	update_env("OLDPWD", get_envlst_value("PWD", m_shell), false, m_shell); //update OLDPWD to PWD
	home = get_envlst_value("HOME", m_shell);
	if (home == NULL)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(home) == 0) //to chg to HOME dir and update PWD to HOME
	{
		update_env("PWD", home, false, m_shell);
		return (0);
	}
	return (1);
}

/*
*	@brief change to the previous directory
*	@return 0 if success update pwd, 1 if failed print error
*/
static int	return_dir(t_minishell *m_shell)
{
	if (get_envlst_value("OLDPWD", m_shell) == NULL)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	if (chdir(get_envlst_value("OLDPWD", m_shell)) == 0) //to chg to OLPWD dir and update PWD to OLDPWD
	{
		update_env("PWD", get_envlst_value("OLDPWD", m_shell), false, m_shell);
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
	update_env("OLDPWD", get_envlst_value("PWD", m_shell), false, m_shell);
	return (chg_pwd(m_shell)); //if not main_dir or return_dir, update PWD
}
