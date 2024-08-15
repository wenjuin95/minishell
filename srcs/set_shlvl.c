/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:37:45 by welow             #+#    #+#             */
/*   Updated: 2024/08/12 14:39:38 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief create a new environment variable for SHLVL
*	@param pos the position of the new SHLVL
*	@param new_value the new value of SHLVL
*	@param m_shell the minishell struct
*	@return char** the updated environment storage
*/
char	**create_new_env(int pos, char *new_value, t_minishell *m_shell)
{
	char	**new_env_storage;
	int		i;

	new_env_storage = malloc(sizeof(char *) * (pos + 2));
	if (new_env_storage == NULL)
		return (NULL);
	i = 0;
	while (i < pos)
	{
		new_env_storage[i] = m_shell->env_storage[i];
		i++;
	}
	new_env_storage[pos] = malloc(ft_strlen("SHLVL=")
			+ ft_strlen(new_value) + 1);
	ft_strlcpy(new_env_storage[pos], "SHLVL=", 6);
	ft_strlcat(new_env_storage[pos], new_value, ft_strlen("SHLVL=")
		+ ft_strlen(new_value) + 1);
	new_env_storage[pos + 1] = NULL;
	return (new_env_storage);
}

/*
*	@brief set the new value of SHLVL
*	@param m_shell the minishell struct
*	@param new_value the new value of SHLVL
*/
void	set_shlvl(t_minishell *m_shell, char *new_value)
{
	int		i;

	i = 0;
	while (m_shell->env[i])
	{
		if (ft_strncmp(m_shell->env[i], "SHLVL", 5) == 0)
		{
			ft_strlcpy(m_shell->env[i] + 6, new_value,
				ft_strlen(new_value) + 1);
			free(new_value);
			break ;
		}
		i++;
	}
}

/*
*	@brief change the value of SHLVL by 1 (for new minishell)
*	@param m_shell the minishell struct
*/
void	change_shlvl(t_minishell *m_shell)
{
	int		shlvl;
	char	*shlvl_str;

	shlvl = atoi(getenv("SHLVL")) + 1;
	shlvl_str = ft_itoa(shlvl);
	set_shlvl(m_shell, shlvl_str);
}
