/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:57:54 by welow             #+#    #+#             */
/*   Updated: 2024/05/21 15:31:18 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//check whether had "-n" in echo command
static int	check_n(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] != '-')
			return (0);
		i++;
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

//function for echo command
/*
* @function  :: echo
* @param arg :: argument for echo command
* @return 0  :: success
* @return 1  :: fail
* n_flag     :: flag for -n
*/
int	echo(char **arg)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (arg[i] != NULL && check_n(arg[i]) == 1)
	{
		n_flag = 1;
		i++;
	}
	while (arg[i] != NULL)
	{
		printf("%s", arg[i]);
		if (arg[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	return (0);
}
