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
*	@brief get value from env_lst with the name
*	@param name name of the environment variable
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
*/
static int	chg_pwd(t_minishell *m_shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	update_env("PWD", pwd, false, m_shell); //update PWD
	return (0);
}

/*
*	@brief change to main directory
*/
static int	main_dir(t_minishell *m_shell)
{
	char	*home;

	update_env("OLDPWD", get_envlst_value("PWD", m_shell), false, m_shell); //update OLDPWD
	home = get_envlst_value("HOME", m_shell);
	if (home == NULL)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(home) == 0) //if success
	{
		update_env("PWD", home, false, m_shell); //update PWD
		return (0);
	}
	return (1);
}

/*
*	@brief change to the previous directory
*/
static int	return_dir(t_minishell *m_shell)
{
	if (get_envlst_value("OLDPWD", m_shell) == NULL)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	if (chdir(get_envlst_value("OLDPWD", m_shell)) == 0) //if success
	{
		update_env("PWD", get_envlst_value("OLDPWD", m_shell), false, m_shell); //update PWD
		return (0);
	}
	return (1);
}

int	cd_option(t_minishell *m_shell, char **cmd)
{
	int	i;

	i = 1;
	if (cmd[i] == NULL || cmd[i][0] == '~') //cd no argument
		return (main_dir(m_shell));
	if (cmd[i][0] == '-') //"cd -" option
		return (return_dir(m_shell));
	if (chdir(cmd[i]) == -1) //if no such file or directory
	{
		printf("minishell: cd: %s: No such file or directory\n", cmd[i]);
		return (1);
	}
	update_env("OLDPWD", get_envlst_value("PWD", m_shell), false, m_shell); //update OLDPWD
	return (chg_pwd(m_shell)); //update PWD
}
