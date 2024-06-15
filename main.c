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

/*
* 	@brief	check directory used
*	@param 	str		prompt name
*	@return	char*	prompt name with directory
*/
static char *ft_dir_debug(char *str)
{
	char *pwd = getcwd(NULL, 0);
	char *prompt = ft_strjoin(str, pwd);
	free(pwd);
	char *prompt2 = ft_strjoin(prompt, ARROW);
	free(prompt);
	return (prompt2);
}

/*
* 	@brief	find the cmd and execute
*	@param 	cmd :: cmd to execute
*	@param 	env_list :: environment list
*/
static void	check_input(char **cmd, t_env_list *env_list)
{
	if (*cmd == NULL)
		return ;
	if (ft_strncmp(*cmd, "env", 3) == 0) //if "env" execute env
		env_option(env_list, cmd);
	if (ft_strncmp(*cmd, "echo", 4) == 0) //if "echo" execute echo
		echo_option(cmd);
	if (ft_strncmp(*cmd, "pwd", 3) == 0) //if "pwd" execute pwd
		pwd_option(cmd);
	if (ft_strncmp(*cmd, "export", 6) == 0) //if "export" execute export
		export_option(env_list, cmd);
	if (ft_strncmp(*cmd, "unset", 5) == 0) //if "unset" execute unset
		unset_option(env_list, cmd);
	if (ft_strncmp(*cmd, "exit", 5) == 0) //if "exit" execute exit
		exit(0); //test
	if (ft_strncmp(*cmd, "cd", 2) == 0) //if "cd" execute cd
		cd_option(env_list, cmd);
}

static void	start_minishell(t_minishell m_shell)
{
	handle_signal(); 

	while (1)
	{
		/*****************************************/
		//directory with prompt name [debug]
		char *prompt2 = ft_dir_debug(PROMPT);
		m_shell.cmd = readline(prompt2);
		/*****************************************/
		// m_shell.cmd = readline(PROMPT);
		if (m_shell.cmd == NULL) //if ctrl + D
		{
			printf("exit\n");
			free(prompt2); //get directory [debug]
			// clear_env_list(m_shell.env_list); //clean the env list
			// ft_clean_cmd(m_shell, 1); //clean the minishell cmd
			ft_clean(m_shell, FALSE, FALSE, TRUE);
			exit(EXIT_SUCCESS);
		}

		add_history(m_shell.cmd); //add to history

		m_shell.split_cmd = ft_split(m_shell.cmd, ' '); //split the cmd
		check_input(m_shell.split_cmd, m_shell.env_list); //check input
		
		free(prompt2); //get directory [debug]
		// ft_clean_cmd(m_shell, 0); //clean the minishell cmd
		ft_clean(m_shell, TRUE, TRUE, FALSE);
	}
	// clear_env_list(m_shell.env_list); //clean the env list
	// ft_clean_cmd(m_shell, 1); //clean the minishell cmd
	ft_clean(m_shell, TRUE, TRUE, TRUE);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	m_shell;

	(void)av;
	(void)ac;
	ft_memset(&m_shell, 0, sizeof(t_minishell)); //set all to NULL/0
	m_shell.env_list = store_env(envp);
	start_minishell(m_shell);
	return (0);
}
