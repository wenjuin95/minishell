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

void check_input(char *input)
{
	if (strncmp(input, "history", 8) == 0) //if "history" execute history list
		print_history();
	if (strncmp(input, "exit", 5) == 0) //if "exit" execute exit
		exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	char	*input;

	(void)av;
	if (ac > 1)
	{
		printf("no arguments needed\n");
		return (1);
	}
	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL) //if ctrl + D
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		add_history(input); //add to history
		store_history(input); //store input
		check_input(input); //check token
	}
	return (0);
}
