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

static void	check_input(char **cmd, t_env_list *env_list)
{
	if (ft_strncmp(*cmd, "env", 3) == 0) //if "env" execute env
		env_option(env_list, cmd);
	if (ft_strncmp(*cmd, "echo", 4) == 0) //if "echo" execute echo
		echo_option(cmd);
	if (ft_strncmp(*cmd, "pwd", 3) == 0) //if "pwd" execute pwd
		pwd_option(cmd);
	if (ft_strncmp(*cmd, "export", 6) == 0) //if "export" execute export
		export_option(env_list, cmd);
	// if (ft_strncmp(*cmd, "exit", 5) == 0) //if "exit" execute exit
	// 	exit_option(cmd);
	// if (ft_strncmp(*cmd, "cd", 2) == 0) //if "cd" execute cd
	// 	cd_option(env_list, cmd);
	// if (ft_strncmp(*cmd, "unset", 5) == 0) //if "unset" execute unset
	// 	unset_option(env_list, cmd);
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
		//get directory
		char *pwd = getcwd(NULL, 0);
		char *prompt = ft_strjoin(PROMPT, pwd);
		free(pwd);
		char *prompt2 = ft_strjoin(prompt, ARROW);
		free(prompt);
		cmd = readline(prompt2);
		// cmd = readline(PROMPT);
		if (cmd == NULL) //if ctrl + D
		{
			printf("exit\n");
			free(cmd);
			free(prompt2);
			clear_env_list(env_list);
			exit(EXIT_SUCCESS);
		}
		//TODO :: parsing
		add_history(cmd); //add to history
		char **split_word = ft_split(cmd, ' ');
		free(cmd);
		check_input(split_word, env_list); //check input

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
		free_2d(split_word); 
		free(cmd);
		clear_env_list(env_list);
	}
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
