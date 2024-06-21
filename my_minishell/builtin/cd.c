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
*	@brief	search the environment variable in the link list and return the value
*	@param	env_list :: pointer to the link list
*	@param	env_name :: name of the environment variable you looking for
*	@return	value of the environment variable you looking for
*	@note need to free
*/
char	*search_env_value(t_env_list *env_list, char *env_name)
{
	t_env_list	*current;
	char		*value;

	current = env_list;
	while (current)
	{
		if (ft_strncmp(env_name, current->env_var, ft_strlen(env_name)) == 0)
		{
			value = get_value(current->env_var);
			return (value);
		}
		current = current->next;
	}
	return (NULL);
}

/*
*	@brief	return error massage
*	@param	cmd :: command
*	@return	1 mean fail
*/
int	get_err(char *cmd)
{
	ft_printf("minishell: cd: %s: No such file or directory\n", cmd);
	return (1);
}

/*
*	@brief	change the directory to main directory
*	@param	env_list :: pointer to the link list
*	@param	home_value :: value of the HOME environment variable
*	@param	pwd_value :: value of the PWD environment variable
*	@return	0 if success, 1 if fail
*/
int	main_dir(t_env_list *env_list, char *home_value, char *pwd_value)
{
	replace_env_var(env_list, ft_strjoin("OLDPWD=", pwd_value));
	free(pwd_value);
	if (home_value == NULL)
	{
		ft_printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(home_value) == 0)
	{
		replace_env_var(env_list, ft_strjoin("PWD=", home_value));
		free(home_value);
		return (0);
	}
	return (1);
}

/*
*	@brief change the PWD environment variable
*	@param	env_list :: pointer to the link list
* 	@return	0 if success, 1 if fail
*/
int	chg_pwd(t_env_list *env_list)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	replace_env_var(env_list, ft_strjoin("PWD=", pwd));
	free(pwd);
	return (0);
}

/*
*	@brief	cd option
*	@param	env_list :: pointer to the link list
*	@param	cmd :: command
*	@return	0 if success, 1 if fail
*/
int	cd_option(t_env_list *env_list, char **cmd)
{
	t_env_list	*current;
	char		*pwd;
	char		*home;
	char		*return_dir;
	int			i;

	i = 1;
	home = search_env_value(env_list, "HOME");
	pwd = search_env_value(env_list, "PWD");
	current = env_list;
	if (cmd[i] == NULL || cmd[i][0] == '~')
		return (main_dir(current, home, pwd));
	if (cmd[i][0] == '-')
	{
		return_dir = search_env_value(env_list, "OLDPWD");
		if (chdir(return_dir) != 0)
			return (free(pwd), free(home), free(return_dir), get_err(cmd[i]));
		replace_env_var(current, ft_strjoin("OLDPWD=", pwd));
		return (free(pwd), free(home), free(return_dir), chg_pwd(current));
	}
	if (chdir(cmd[i]) != 0)
		return (free(pwd), free(home), get_err(cmd[i]));
	replace_env_var(current, ft_strjoin("OLDPWD=", pwd));
	return (free(pwd), free(home), chg_pwd(current));
}
