/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:57:54 by welow             #+#    #+#             */
/*   Updated: 2024/06/26 13:38:42 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	TODO:
*	1. echo
*	2. echo -n
*	3. echo [any argument]
*	4. echo -n [any argument]
*/

/*
*	@brief	check for -n flag in the argument
*	@param	arg :: argument to check
*	@return	true if -n flag is present, false if not
*/
static bool	check_n_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (false);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

/*
*	@brief	handle echo command
*	@param	cmd :: argument to print
*	@return	0 if success
*/
int	echo_option(char **cmd)
{
	int	i;
	int	n_flag;

	i = 1; //skip the "echo"
	n_flag = false;
	while (cmd[i] != NULL && check_n_flag(cmd[i]) == true) //check for -n flag in the argument
	{
		n_flag = true;
		i++;
	}
	while (cmd[i] != NULL)
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL) //if not last argument
			printf(" "); //print space and continue
		i++;
	}
	if (n_flag == false) //check if -n flag is not present
		printf("\n");
	return (0);
}
