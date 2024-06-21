/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:57:54 by welow             #+#    #+#             */
/*   Updated: 2024/06/17 16:46:43 by welow            ###   ########.fr       */
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
*	@return	TRUE if -n flag is present, FALSE if not
*/
static int	check_n_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (FALSE);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
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
	n_flag = FALSE;
	while (cmd[i] != NULL && check_n_flag(cmd[i]) == TRUE) //check for -n flag in the argument
	{
		n_flag = TRUE;
		i++;
	}
	while (cmd[i] != NULL)
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL) //if not last argument
			printf(" "); //print space and continue
		i++;
	}
	if (n_flag == FALSE) //check if -n flag is not present
		printf("\n");
	return (0);
}
