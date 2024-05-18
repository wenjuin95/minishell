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

void check_input(char *input, char **env_storage)
{
	if (ft_strncmp(input, "history", 8) == 0) //if "history" execute history list
		print_history();
	if (ft_strncmp(input, "exit", 5) == 0) //if "exit" execute exit
		exit(EXIT_SUCCESS);
	if (ft_strncmp(input, "env", 3) == 0) //if "env" execute env
		print_environment(env_storage);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**env_storage;

	//void av and control the length
	(void)av;
	if (ac > 1)
	{
		printf("no arguments needed\n");
		return (1);
	}

	//store environment variable
	env_storage = store_env(envp);
	
	//handler ctrl+c, "ctrl + \"
	handle_signal();

	//begin the terminal 
	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL) //if ctrl + D
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		//TODO :: parsing
		add_history(input); //add to history
		store_history(input); //store input
		check_input(input, env_storage); //check input
		free(input);
		free(env_storage);
	}
	return (0);
}
