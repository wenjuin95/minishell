/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:46:39 by welow             #+#    #+#             */
/*   Updated: 2024/06/23 13:22:47 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	handle exit command
*	1. exit
*	2. exit [any argument with digit]
*	3. exit [any argument with non-digit]
*/

// /*
// *	@brief	choose section for exit output and return the exit code
// *	@param	cmd	argument to check
// *	@param	section	section to check
// *	@return	1 if too many argument, 2 if is not a digit, 0 if success
// */
// static int exit_output(char **cmd, int section)
// {
// 	if (section == 1) //too many argument
// 	{
// 		ft_printf("exit\nminishell: exit: too many arguments\n");
// 		return (1);
// 	}
// 	else if (section == 2) //is not a digit
// 	{
// 		ft_printf("exit\nminishell: exit: %s: numeric argument required\n",
// 			cmd[1]);
// 		return (2);
// 	}
// 	return (0);
// }

// /*
// *	@brief	handle exit command
// *	@param	cmd	argument to check
// *	@return	0 if success, exit code if the return not 0 
// */
// int exit_option(char **cmd)
// {
// 	int	i;
// 	int	nb;
	
// 	i = -1;
// 	//if the pointer had "exit" and second element is not empty
// 	if (*cmd != NULL && cmd[1] != NULL)
// 	{
// 		//check if the second element is a digit (if yes then return numeric argument required)
// 		while (cmd[1][++i])
// 			if (ft_isdigit(cmd[1][i]) == FALSE)
// 				return (exit_output(cmd, 2));
// 		nb = ft_atoi(cmd[1]); //if is digit then assign to nb and return
// 		exit(nb % 256);
// 		if (cmd[2] != NULL) //check if any more argument);
// 			return (exit_output(cmd, 1));
// 	}
// 	exit(0);
// }

/*
*	exit
*	- you just exit and return 0
*	
*	exit 123
*	- you exit and return 123
*
*	exit 123 456
*	- you can't exit but print exit and print error
*
*	exit 123 das
*	- you can't exit but print exit and print error
*	
*	exit asda
*	- you exit and print exit and print error
*	return (255);
*
*  exit dada dadas
*	- you exit and print exit and print error
*	return (255)
*/

/*
*	@brief	print exit message
*	@param	cmd :: argument to check
*	@param	return_value :: return value
*	@return	1 if too many argument, 2 if is not a digit, 0 if success
*/
static int	ft_exit_msg(char *cmd, int return_value)
{
	if (return_value == 1)
	{
		ft_printf("exit\n");
		ft_printf("minishell: exit: too many arguments\n");
		return (1);
	}
	else if (return_value == 255)
	{
		ft_printf("exit\n");
		ft_printf("minishell: exit: %s: numeric argument required\n", cmd);
		return (255);
	}
	return (0);
}

static void	ft_space_sign(char *cmd, int *i, int *sign)
{
	while (ft_isspace(cmd[*i]) == TRUE)
		(*i)++;
	if (cmd[*i] == '+' || cmd[*i] == '-')
	{
		if (cmd[*i] == '-')
			*sign = -1;
		(*i)++;
	}	
}

/*
*	@brief	convert string to digit and check if it is not a digit then exit
*	@param	m_shell :: minishell struct
*	@param	cmd :: argument to check
*	@return	nb(exit_code)
*/
static int	ft_exit_digit(char *cmd)
{
	int				i;
	int				sign;
	int				exit_code;
	unsigned long	nb;

	i = 0;
	sign = 1;
	ft_space_sign(cmd, &i, &sign);
	if (ft_isdigit(cmd[i]) == FALSE) //if the 1st arg not a digit
	{
		exit_code = ft_exit_msg(cmd, 255);
		(ft_clean(FALSE), exit(exit_code));
	}
	nb = 0;
	while (cmd[i])
	{
		nb = (nb * 10) + (cmd[i] - '0');
		i++;
	}
	return ((nb * sign) % 256);
}

/*
*	@brief	handle exit command
*	@param	m_shell :: minishell struct
*	@param	cmd :: argument to check
*	@note	exit with the (exit_code) given
*	@note	if too many arg then continue without exit
*/
void	exit_option(char **cmd)
{
	int	exit_code;

	exit_code = m_shell.exit_code;
	if (cmd[1] != NULL) //if first arg available
	{
		if (cmd[2] != NULL && ft_isdigit(cmd[1][0]) == FALSE) //if 2nd arg available and if 1st arg is not nb
		{
			exit_code = ft_exit_msg(cmd[1], 255);
			(ft_clean(FALSE), exit(exit_code));
		}
		else if (cmd[2] != NULL) //if 2nd arg available and if 1st arg is nb
		{
			exit_code = ft_exit_msg(cmd[1], 1);
			return ;
		}
		else //if 2nd arg not available
		{
			exit_code = ft_exit_digit(cmd[1]);
			ft_printf("exit\n");
		}
	}
	ft_clean(FALSE); //if 1st arg not available
	exit(exit_code);
}