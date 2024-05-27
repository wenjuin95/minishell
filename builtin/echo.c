/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:57:54 by welow             #+#    #+#             */
/*   Updated: 2024/05/27 13:31:11 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//check for -n flag
static int	check_n_flag(char *arg)
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
int	echo_option(char **arg)
{
	int	i;
	int	n_flag;
	
	i = 1; //skip the "echo"
	n_flag = 0;
	while (arg[i] != NULL && check_n_flag(arg[i]) == TRUE) //check for -n flag in the argument
	{
		n_flag = 1;
		i++;
	}
	while (arg[i] != NULL)
	{
		printf("%s", arg[i]);
		if (arg[i + 1] != NULL) //if not last argument
			printf(" "); //print space and continue
		i++;
	}
	if (n_flag == 0) //check if -n flag is not present
		printf("\n");
	return (0);
}
