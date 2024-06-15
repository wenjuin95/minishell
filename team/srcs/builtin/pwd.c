/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:10:04 by welow             #+#    #+#             */
/*   Updated: 2024/06/14 11:11:20 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	handle pwd command
*	1. pwd
*/

/*
*	@brief	handle pwd command
*	@param	cmd :: argument to check
*	@return	0 if success, 1 if fail
*/
int	pwd_option(char **cmd)
{
	int		i;
	char	*pwd;

	i = 1;
	if (cmd[i] == NULL)
	{
		pwd = NULL;
		pwd = getcwd(pwd, 0);
		printf("%s\n", pwd);
		free(pwd);
		return (0);
	}
	else
	{
		printf("pwd: %s: No such file or directory\n", cmd[i]);
		return (1);
	}
}