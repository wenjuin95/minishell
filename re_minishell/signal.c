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

void handle_ctrl_c(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line(); //move "minishell>" to a newline
	rl_replace_line("", 0); //clear the current line
	rl_redisplay(); //redisplay the "minishell>"
}

void handle_signal(void)
{
	signal(SIGINT, handle_ctrl_c); //ctrl + c
	signal(SIGQUIT, SIG_IGN); //"ctrl + \" ignore (SIG_IGN is a macro that ignores the signal)
}