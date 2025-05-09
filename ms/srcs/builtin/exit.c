/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:46:39 by welow             #+#    #+#             */
/*   Updated: 2024/08/20 20:21:55 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	TODO:
*	1. exit
*	2. exit [any argument with digit]
*	3. exit [any argument with non-digit]
*
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
*	@param	cmd argument
*	@param	return_value return value
*	@return	1 if too many argument, 255 if is not a digit, 0 if success
*/
static int	ft_exit_msg(char *cmd, int return_value)
{
	if (return_value == EXIT_FAILURE)
	{
		ft_printf("exit\n");
		ft_printf("minishell: exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	else if (return_value == NOT_DIGIT)
	{
		ft_printf("exit\n");
		ft_printf("minishell: exit: %s: numeric argument required\n", cmd);
		return (NOT_DIGIT);
	}
	return (0);
}

/*
*	@brief check if the argument is not a digit then print error and exit
*	@param	m_shell get exit code and link list from m_shell
*	@param	cmd argument
*	@param	i index of the argument
*/
static void	exit_if_not_digit(t_minishell *m_shell, char *cmd, int i)
{
	if (ft_isdigit(cmd[i]) == false)
	{
		m_shell->exit_code = ft_exit_msg(cmd, NOT_DIGIT);
		ft_clean(m_shell);
		exit(m_shell->exit_code);
	}
}

/*
*	@brief	convert string to digit and check if it is not a digit then exit
*	@param	m_shell get exit code and link list from m_shell
*	@param	cmd argument to check
*	@return	nb(exit_code)
*/
static int	ft_exit_digit(t_minishell *m_shell, char *cmd)
{
	int				i;
	int				sign;
	unsigned long	nb;

	i = 0;
	sign = 1;
	while (ft_isspace(cmd[i]) == true)
		i++;
	if (cmd[i] == '+' || cmd[i] == '-')
	{
		if (cmd[i] == '-')
			sign = -1;
		i++;
	}
	exit_if_not_digit(m_shell, cmd, i);
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
*	@param	m_shell get exit code and link list from m_shell
*	@param	cmd argument
*	@note	exit with the (exit_code) given
*	@note	if too many arg then continue without exit
*/
void	exit_option(char **cmd, t_minishell *m_shell)
{
	if (cmd[1] != NULL)
	{
		if (cmd[2] != NULL && ft_isdigit(cmd[1][0]) == false)
		{
			m_shell->exit_code = ft_exit_msg(cmd[1], NOT_DIGIT);
			(ft_clean(m_shell), exit(m_shell->exit_code));
		}
		else if (cmd[2] != NULL)
		{
			m_shell->exit_code = ft_exit_msg(cmd[1], EXIT_FAILURE);
			return ;
		}
		else
		{
			m_shell->exit_code = ft_exit_digit(m_shell, cmd[1]);
			ft_printf("exit\n");
		}
	}
	ft_clean(m_shell);
	exit(m_shell->exit_code);
}
