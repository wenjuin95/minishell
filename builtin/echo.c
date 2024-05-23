/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:57:54 by welow             #+#    #+#             */
/*   Updated: 2024/05/22 14:36:49 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//check whether had "-n" in echo command
static int	check_for_n(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] != '-')
			return (FALSE);
		i++;
		if (arg[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

//function for echo option
/*
* @function  :: check echo option
* @param arg :: echo option
* @return 0  :: success
* @return 1  :: fail
* n_flag     :: flag for -n
*/
int	echo_option(char **arg)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = FALSE;
	while (arg[i] != NULL && check_for_n(arg[i]) == TRUE)
	{
		n_flag = TRUE;
		i++;
	}
	while (arg[i] != NULL)
	{
		printf("%s", arg[i]);
		if (arg[i + 1] != NULL) //if not last argument
			printf(" "); //print space and continue
		i++;
	}
	if (n_flag == FALSE) 
		printf("\n");
	return (0);
}
