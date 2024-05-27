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

#include "../minishell.h"

//function get directory

//function for cd
int	cd_option(char **env_storage, char **cmd)
{
	char	*path;

	if (cmd[1] == NULL)
		chdir(getenv("HOME")); //change directory to home
	else if (chdir(cmd[1]) == -1)
		ft_printf("cd: %s: No such file or directory\n", cmd[1]);
	else
	{
		//TODO: get the current path and assign to path then append to env_storage
		path = 
	}
}