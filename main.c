/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:00:58 by welow             #+#    #+#             */
/*   Updated: 2024/05/09 19:00:58 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void signal_handler(int signum)
{
	(void)signum;
	ft_printf("\n");
	rl_on_new_line(); //reset the readline library
	rl_redisplay(); //redisplay the prompt
}

void check_input(char *input)
{
	if (strncmp(input, "history", 8) == 0) //if "history" execute history list
		print_history();
	if (strncmp(input, "exit", 5) == 0) //if "exit" execute exit
		exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char **env = envp;

	//void av and control thr length
	(void)av;
	if (ac > 1)
	{
		printf("no arguments needed\n");
		return (1);
	}

	//get the environment variable
	while (*env)
	{
		//TODO: store the environment variable
		//ft_printf("%s\n", *env); //print the environment variable
		env++;
	}

	//handler ctrl+c, "ctrl + \"
	signal(SIGINT, signal_handler); //ctrl + c
	signal(SIGQUIT, SIG_IGN); //"ctrl + \" ignore (SIG_IGN is a macro that ignores the signal)

	//begin the terminal 
	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL) //if ctrl + D
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		add_history(input); //add to history
		store_history(input); //store input
		check_input(input); //check input
		//TODO :: parsing
		free(input);
	}
	return (0);
}
