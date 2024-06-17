/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:45:33 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/17 16:56:00 by welow            ###   ########.fr       */
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
		m_shell.line = readline(PROMPT); //define PROMPT in minishell.h
		if (m_shell.line == NULL) //if ctrl + D
		{
			ft_printf("exit\n");
			ft_clean(m_shell, FALSE, TRUE);
			exit(0);
		}
		add_history(m_shell.line); //add to history
		
		//parse
		parse(m_shell.line); //parse the line
		
		//builtin
		m_shell.split_cmd = ft_split(m_shell.line, ' '); //split the cmd
		check_input(m_shell.split_cmd, m_shell); //check input
		
		ft_clean(m_shell, TRUE, FALSE);
	}
	ft_clean(m_shell, TRUE, TRUE);
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