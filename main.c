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

static void check_input(char *cmd, t_env_list *env_list)
{
	if (ft_strncmp(cmd, "exit", 5) == 0) //if "exit" execute exit
		exit(EXIT_SUCCESS);
	if (ft_strncmp(cmd, "env", 3) == 0) //if "env" execute env
		print_env(env_list);
}

static void	start_minishell(t_env_list *env_list)
{
	char	*cmd;

	handle_signal();
	
	//TODO ::setup minishell with the terminal
	//handler ctrl+c, "ctrl + \"

	//begin the terminal 
	while (1)
	{
		cmd = readline("minishell$ ");
		if (cmd == NULL) //if ctrl + D
		{
			printf("exit\n");
			free(cmd);
			clear_env_list(env_list);
			exit(EXIT_SUCCESS);
		}
		//TODO :: parsing
		add_history(cmd); //add to history
		check_input(cmd, env_list); //check input

		/**********************************************/
		/*
		TODO :: 1. parsing
				2. tokenize
				3. fork
		*/
		//just a testing
		// char pid = fork();
		// if (pid == 0)
		// {
		// 	execute_cmd(cmd, env_storage);
		// 	exit(EXIT_SUCCESS);
		// }
		// else
		// 	wait(NULL);
		/****************************************/
		free(cmd);
	}
	clear_env_list(env_list);
}

int	main(int ac, char **av, char **envp)
{
	t_env_list *env_list;
	//TODO :: setup environment
	//store environment variable
	env_list = store_env(envp);
	(void)av;
	(void)ac;
	start_minishell(env_list);
	return (0);
}
