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
* 	@brief	modi the prompt to include the directory
*	@param 	str		prompt name
*	@return	prompt name with directory
*/
static char	*readline_dir(char *str)
{
	char	*pwd;
	char	*prompt;
	char	*updated_prompt;
	char	*line;

	pwd = getcwd(NULL, 0);
	prompt = ft_strjoin(str, pwd);
	free(pwd);
	updated_prompt = ft_strjoin(prompt, ARROW);
	free(prompt);
	line = readline(updated_prompt);
	free(updated_prompt);
	return (line);
}

/*
* 	@brief	find the cmd and execute
*	@param 	cmd :: cmd to execute
*	@param 	env_list :: environment list
*/
static void	check_input(char **cmd, t_minishell m_shell)
{
	if (*cmd == NULL)
		return ;
	if (ft_strncmp(*cmd, "env", 3) == 0) //if "env" execute env
		env_option(m_shell.env_list, cmd);
	if (ft_strncmp(*cmd, "echo", 4) == 0) //if "echo" execute echo
		echo_option(cmd);
	if (ft_strncmp(*cmd, "pwd", 3) == 0) //if "pwd" execute pwd
		pwd_option(cmd);
	if (ft_strncmp(*cmd, "export", 6) == 0) //if "export" execute export
		export_option(m_shell.env_list, cmd);
	if (ft_strncmp(*cmd, "unset", 5) == 0) //if "unset" execute unset
		unset_option(m_shell.env_list, cmd);
	if (ft_strncmp(*cmd, "exit", 5) == 0) //if "exit" execute exit
		exit_option(m_shell, cmd);
	if (ft_strncmp(*cmd, "cd", 2) == 0) //if "cd" execute cd
		cd_option(m_shell.env_list, cmd);
}

static void	start_minishell(t_minishell m_shell)
{
	handle_signal();
	while (1)
	{
		m_shell.cmd = readline_dir(PROMPT);
		if (m_shell.cmd == NULL) //if ctrl + D
		{
			printf("exit\n");
			ft_clean(m_shell, FALSE, TRUE);
			exit(EXIT_SUCCESS);
		}

		add_history(m_shell.cmd); //add to history

		m_shell.split_cmd = ft_split(m_shell.cmd, ' '); //split the cmd
		check_input(m_shell.split_cmd, m_shell); //check input

		ft_clean(m_shell, TRUE, FALSE);
	}
	ft_clean(m_shell, TRUE, TRUE);
	clear_history();
}

int	main(int ac, char **av, char **envp)
{

	(void)av;
	(void)ac;
	ft_memset(&m_shell, 0, sizeof(t_minishell)); //set all to NULL/0
	m_shell.env_storage = envp;
	store_env(void);
	start_minishell(m_shell);
	return (0);
}
