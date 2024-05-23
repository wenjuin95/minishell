/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:46:39 by welow             #+#    #+#             */
/*   Updated: 2024/05/22 15:25:26 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_digit(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/*
*	handle exit command
*	exit 12314       :: ok
*	exit             :: ok
*	exit 12314 12314 :: extra argument
*	exit 12314a      :: not a number
*
*/
void	exit_option(char **cmd)
{
	if (cmd[1] != NULL && cmd[2] != NULL)
	{
		ft_printf("minishell: exit: too many arguments\n");
		exit(1);
	}
	else if (cmd[1] != NULL && check_digit(cmd[1]) == TRUE)
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
	}
	else if (cmd[1] != NULL)
	{
		ft_printf("exit\n");
		exit(ft_atoi(cmd[1]));
	}
	else
	{
		ft_printf("exit\n");
		exit(0);
	}
}
