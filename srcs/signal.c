/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:50:29 by welow             #+#    #+#             */
/*   Updated: 2024/05/13 12:50:29 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief	change signal in child process
*	@param	is_child check if signal is for child process
*	@param	m_shell get the original termios and new termios form m_shell
*	@note	reset signal to default and change signal according to is_child
*	@note	is_child == true, signal(SIGINT, handle_child_signal)
*	@note	is_child == false, handle_signal(m_shell)
*/
void	change_signal(bool is_child)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_child)
	{
		signal(SIGINT, handle_child_signal);
		signal(SIGQUIT, handle_child_exit_signal);
	}
	else
	{
		signal(SIGINT, handle_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
}

/*
*	@brief handle ctrl + c signal
*	@note	rl_on_new_line() move "minishell>" to a newline
*	@note	rl_replace_line("", 0) clear the current line
*	@note	rl_redisplay() redisplay the prompt
*/
void	handle_ctrl_c(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*
*	@brief handle child signal for ctrl+c
*	@note	rl_on_new_line() move "minishell>" to a newline
*	@note	rl_replace_line("", 0) clear the current line
*	@note 	not using rl_redisplay() because it will cause 
*			the prompt to be displayed twice with readline
*/
void	handle_child_signal(int signum)
{
	if (signum == SIGINT)
		rl_replace_line("", 0);
}

/*
*	@brief handle child signal for ctrl+\ (quit)
*	@note	print "Quit" when signal is received
*/
void	handle_child_exit_signal(int signum)
{
	if (signum == SIGQUIT)
		ft_printf("Quit\n");
}

/*
*	@brief mute signal return when ctrl + C, \, D is pressed
*	@param m_shell minishell struct
*/
void	mute_signal(t_minishell *m_shell)
{
	tcgetattr(STDIN_FILENO, &m_shell->term);
	m_shell->term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &m_shell->term);
}
