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

void	ft_clean(t_minishell m_shell)
{
	free(m_shell.cmd);
	if (m_shell.split_word != NULL)
		free_2d(m_shell.split_word);
}

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

static void	start_minishell(t_minishell m_shell, t_env_list *env_list)
{
	handle_signal();
	
	//TODO ::setup minishell with the terminal
	//handler ctrl+c, "ctrl + \"

	//begin the terminal 
	while (1)
	{
		//get directory
		// char *pwd = getcwd(NULL, 0);
		// char *prompt = ft_strjoin(PROMPT, pwd);
		// free(pwd);
		// char *prompt2 = ft_strjoin(prompt, ARROW);
		// free(prompt);
		// cmd = readline(prompt2);
		m_shell.cmd = readline(PROMPT);
		if (m_shell.cmd == NULL) //if ctrl + D
		{
			printf("exit\n");
			clear_env_list(env_list);
			exit(EXIT_SUCCESS);
		}
		//TODO :: parsing
		add_history(m_shell.cmd); //add to history
		m_shell.split_word = ft_split(m_shell.cmd, ' ');
		check_input(m_shell.split_word, env_list); //check input

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
		ft_clean(m_shell);
	}
	clear_env_list(env_list);
}

int	main(int ac, char **av, char **envp)
{
	t_env_list *env_list;
	t_minishell	m_shell;
	//TODO :: setup environment
	//store environment variable
	env_list = store_env(envp);
	ft_memset(&m_shell, 0, sizeof(t_minishell));
	(void)av;
	(void)ac;
	start_minishell(m_shell, env_list);
	return (0);
}
