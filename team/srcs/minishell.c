/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:45:33 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/14 11:42:46 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(void)
// {
// 	char		*line;

// 	while (1)
// 	{
// 		line = readline("minishell> ");
// 		if (!line || !*line)
// 			break ;
// 		add_history(line);
// 		parse(line);
// 		free(line);
// 	}
// 	clear_history();
// 	return (0);
// }

static void	start_minishell(t_minishell m_shell)
{
	handle_signal(); 
	while (1)
	{
		m_shell.line = readline(PROMPT);
		if (m_shell.line == NULL) //if ctrl + D
		{
			ft_printf("exit\n");
			clear_env_list(m_shell.env_list); //clean the env list
			exit(EXIT_SUCCESS);
		}
		add_history(m_shell.line); //add to history
		//parse
		ft_printf("\033[0;35m----parse----\033[0m\n");
		parse(m_shell.line); //parse the line
		//builtin
		ft_printf("\n\033[0;33m----Builtin----\033[0m\n");
		m_shell.split_cmd = ft_split(m_shell.line, ' '); //split the cmd
		check_input(m_shell.split_cmd, m_shell.env_list); //check input
		
		ft_clean_cmd(m_shell); //clean the minishell cmd
	}
	clear_env_list(m_shell.env_list); //clean the env list
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