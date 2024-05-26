/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:10:04 by welow             #+#    #+#             */
/*   Updated: 2024/05/25 14:47:43 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//input should chg
int	pwd(char *cmd)
{
	char	*pwd;

	if (ft_strncmp(&cmd[0], "pwd", 4) != 0)
		return (0);
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}