/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:46:39 by welow             #+#    #+#             */
/*   Updated: 2024/06/07 10:11:37 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
*	handle exit command
*	1. exit
*	2. exit [any argument with digit]
*	3. exit [any argument with non-digit]
*/

//choose section for exit output and return the exit code
static int exit_output(char **cmd, int section)
{
	if (section == 1) //too many argument
	{
		ft_printf("exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	else if (section == 2) //is not a digit
	{
		ft_printf("exit\nminishell: exit: %s: numeric argument required\n",
			cmd[1]);
		return (2);
	}
	return (0);
}

int exit_option(char **cmd)
{
	int	i;
	int	nb;
	
	i = -1;
	//if the pointer had "exit" and second element is not empty
	if (*cmd != NULL && cmd[1] != NULL)
	{
		//check if the second element is a digit (if yes then return numeric argument required)
		while (cmd[1][++i])
			if (ft_isdigit(cmd[1][i]) == FALSE)
				return (exit_output(cmd, 2));
		nb = ft_atoi(cmd[1]); //if is digit then assign to nb and return
		return (nb % 256);
		if (cmd[2] != NULL) //check if any more argument
			return (exit_output(cmd, 1));
	}
	return (0);
}
