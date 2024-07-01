/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:45:33 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/01 13:34:03 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

void	execution_test(char **command, bool only_execute)
{
	t_redir_cmd	rcmd; //redirection command
	t_exec_cmd	ecmd; //execution command
	t_cmd		*cmd; //command

	if (only_execute == true)
	{
		ecmd.argv = command; //command to execute
		ecmd.type = CMD_EXEC; //type of command
		cmd = (t_cmd *)&ecmd; //execution command to command
		eval_tree(cmd); //evaluate command
	}
	else
	{
		ecmd.argv = command; //command to execute
		ecmd.type = CMD_EXEC; //type of command
		rcmd.fd = 1; //file descriptor
		rcmd.filename = "storing_redirect"; //redirection: file name
		rcmd.type = CMD_REDIR; //redirection: type of command
		rcmd.mode_flag = O_CREAT | O_WRONLY | O_TRUNC; //redirection: mode flag
		rcmd.next_cmd = (t_cmd *)&ecmd; //redirection: next command
		cmd = (t_cmd *)&rcmd; //redirection command to command
		eval_tree(cmd); //evaluate command
	}
}

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
	updated_prompt = ft_strjoin(prompt, END_PROMPT);
	free(prompt);
	line = readline(updated_prompt);
	free(updated_prompt);
	return (line);
}

// int	main(void)
// {
// 	char		*line;

// 	execution_test();
// 	while (1)
// 	{
// 		line = readline_dir(PROMPT);
// 		if (!line || !*line)
// 			break ;
// 		add_history(line);
// 		parse(line);
// 		free(line);
// 	}
// 	clear_history();
// 	return (0);
// }

static void	start_minishell(t_minishell *m_shell)
{
	while (1)
	{
		handle_signal();
		m_shell->line = readline_dir(PROMPT);
		if (m_shell->line == NULL)
		{
			ft_clean(m_shell);
			ft_printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		add_history(m_shell->line);
		ft_printf("-----------TOKEN-----------\n");
		parse(m_shell->line);
		ft_printf("\n\n");
		m_shell->split_cmd = ft_split(m_shell->line, ' ');
		if (check_input(*m_shell->split_cmd) == true)
			execute_input(m_shell, m_shell->split_cmd);
		else
			execution_test(m_shell->split_cmd, true);
		free_2d(m_shell->split_cmd);
		free(m_shell->line); //for new command
	}
	ft_clean(m_shell);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	m_shell;

	(void)av;
	(void)ac;
	ft_memset(&m_shell, 0, sizeof(t_minishell));
	m_shell.env_storage = envp;
	store_env(&m_shell);
	start_minishell(&m_shell);
	return (0);
}
