/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:37:45 by welow             #+#    #+#             */
/*   Updated: 2024/10/14 16:32:58 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief set the new value of SHLVL
*	@param m_shell the minishell struct
*	@param new_value the new value of SHLVL
*	@note m_shell->env[i] + 6: to skip the "SHLVL=" part
*/
void	update_shlvl(t_minishell *m_shell, char *new_value)
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
	update_shlvl(m_shell, shlvl_str);
}
