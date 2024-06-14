/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:30:23 by welow             #+#    #+#             */
/*   Updated: 2024/05/18 19:30:23 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief 	free 2d array
*	@param 	str :: 2d array
*/
void free_2d(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

/*
*	@brief	free cmd
*	@param	m_shell :: minishell struct (cmd part)
*/
void	ft_clean_cmd(t_minishell m_shell)
{
	free(m_shell.line);
	if (m_shell.split_cmd != NULL)
		free_2d(m_shell.split_cmd);
}
