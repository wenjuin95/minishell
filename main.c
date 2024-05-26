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

void check_input(char *cmd, char **env_storage)
{
	if (ft_strncmp(cmd, "exit", 5) == 0) //if "exit" execute exit
		exit(EXIT_SUCCESS);
	if (ft_strncmp(cmd, "env", 3) == 0) //if "env" execute env
		print_environment(env_storage);
}

void	start_minishell(char **envp)
{
	char	*cmd;
	char	**env_storage;

	//TODO :: setup environment
	//store environment variable
	env_storage = store_env(envp);
	
	//TODO ::setup minishell with the terminal
	//handler ctrl+c, "ctrl + \"
	handle_signal();

	//begin the terminal 
	while (1)
	{
		cmd = readline("minishell$ ");
		if (cmd == NULL) //if ctrl + D
		{
			printf("exit\n");
			free(cmd);
			free_2d(env_storage);
			exit(EXIT_SUCCESS);
		}
		//TODO :: parsing
		add_history(cmd); //add to history
		check_input(cmd, env_storage); //check input

		/**********************************************/
		/*
		TODO :: 1. parsing
				2. tokenize
				3. fork
		*/
		//just a testing
		char pid = fork();
		if (pid == 0)
		{
			execute_cmd(cmd, env_storage);
		}
		else
			wait(NULL);
		/****************************************/
		free(cmd);
	}
	free(env_storage);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	(void)ac;
	start_minishell(envp);
	return (0);
}
