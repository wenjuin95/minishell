/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:32:25 by welow             #+#    #+#             */
/*   Updated: 2024/05/17 16:32:25 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	TODO:
 *	1. env
 *	2. env [any argument]
 */

/*
*	@brief get name from the env_var
*	@param env_var :: env variable
*	@return name of the env_var
*	@note if no '=' found, return the whole string
*	@note if found '=' then return the string before it
*	@note memory need to be free
*/
char	*get_name(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i])
	{
		if (env_var[i] == '=')
			return (to_gc_lst(ft_substr(env_var, 0, i)));
		i++;
	}
	return (to_gc_lst(ft_strdup(env_var)));
}

/*
*	@brief get value from the env_var
*	@param env_var :: env variable
*	@return value of the env_var
*	@note if no '=' found, return NULL
*	@note if found '=' then return the string after it
*/
char	*get_value(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i])
	{
		if (env_var[i] == '=')
		{
			i++;
			return (to_gc_lst(ft_substr(env_var, i, ft_strlen(env_var) - i)));
		}
		i++;
	}
	return (NULL);
}

/*
*	@brief assign env_storage to env_lst
*	@param m_shell get env array and env link list from m_shell
*	@note if env_storage is NULL, then return
*	@note if env_storage is not NULL, then assign to env_lst
*/
void	store_env(t_minishell *m_shell)
{
	int		i;
	char	**env;
	char	*env_name;
	char	*env_value;

	env = m_shell->env;
	if (env == NULL)
		return ;
	i = -1;
	while (env[++i])
	{
		env_name = get_name(env[i]);
		env_value = get_value(env[i]);
		update_env(env_name, env_value, true, m_shell);
	}
}

/*
*	@brief 	handle env command
*	@param cmd argument
*	@param m_shell get env array and env link list from m_shell
*	@note prevent only name in env lst to be print
*/
int	env_option(char **cmd, t_minishell *m_shell)
{
	t_env_lst	*current;

	if (cmd[1] == NULL)
	{
		current = m_shell->env_lst;
		while (current)
		{
			if (current->value != NULL)
				ft_printf("%s=%s\n", current->name, current->value);
			current = current->next;
		}
	}
	m_shell->exit_code = EXIT_SUCCESS;
	return (m_shell->exit_code);
}
