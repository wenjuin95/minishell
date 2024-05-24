/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:46:39 by welow             #+#    #+#             */
/*   Updated: 2024/05/24 15:02:21 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int exit_output(char **cmd, int section)
{
	if (section == 1)
	{
		ft_printf("exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	else if (section == 2)
	{
		ft_printf("exit\nminishell: exit: %s: numeric argument required\n",
			cmd[1]);
		return (2);
	}
	return (0);
}

int exit_arg(char **cmd)
{
	int	i;
	int	nb;

	i = -1;
	//if the 2d array is not empty and the second element is not empty
	if (*cmd != NULL && cmd[1] != NULL)
	{
		//check if the second element is a digit (if yes then return numeric argument required)
		while (cmd[1][++i])
			if (ft_isdigit(cmd[1][i]) == FALSE)
				return (exit_output(cmd, 2));
		nb = ft_atoi(cmd[1]);
		return (nb % 256);
		//check if there is a third element
		if (cmd[2] != NULL)
			return (exit_output(cmd, 1));
	}
	return (0);
}
