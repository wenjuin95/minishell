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
		if (env_var[i] == '=') //if found '=' then return the string before it
			return (to_gc_lst(ft_substr(env_var, 0, i), 0)); //return the string before '=' //debug
		i++;
	}
	return (to_gc_lst(ft_strdup(env_var), 0)); //if no '=' found, return the whole string
}



/*
*	@brief assign env_storage to env_lst
*	@note if env_storage is NULL, then return
*	@note if env_storage is not NULL, then assign to env_lst
*/
void	store_env(t_minishell *m_shell)
{
	int		i;
	char	**env;
	char	*env_name;
	char	*env_value;

	env = m_shell->env_storage;
	if (env == NULL)
		return ;
	i = -1;
	while (env[++i])
	{
		env_name = get_name(env[i]);
		env_value = getenv(env_name);
		update_env(env_name, env_value, true, m_shell);
	}
}

/*
*	@note prevent only name in env lst to be print
*/
int	env_option(t_minishell *m_shell, char **cmd)
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
	return (0);
}
