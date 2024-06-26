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
*	@brief handle ctrl + c signal
*	@note	rl_on_new_line() move "minishell>" to a newline
*	@note	rl_replace_line("", 0) clear the current line
*	@note	rl_redisplay() redisplay the "minishell>"
*/
static void	handle_ctrl_c(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
*	@brief handle signal
*	@note	signal(SIGINT, handle_ctrl_c) :: ctrl + c
*	@note	signal(SIGQUIT, SIG_IGN) :: "ctrl + \" ignore 
*	(SIG_IGN is a macro that ignores the signal)
*/
void	handle_signal(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}