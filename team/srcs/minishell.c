/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:45:33 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/21 20:33:33 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

void	execution_test(void)
{
	t_redir_cmd	rcmd;
	t_exec_cmd	ecmd;
	const char	*argv[] = {"/bin/ls", "-al", NULL};
	t_cmd		*cmd;

	ecmd.argv = (char **)argv;
	ecmd.type = CMD_EXEC;
	rcmd.fd = 1;
	rcmd.filename = "test";
	rcmd.type = CMD_REDIR;
	rcmd.mode_flag = O_CREAT | O_WRONLY | O_TRUNC;
	rcmd.next_cmd = (t_cmd *)&ecmd;
	cmd = (t_cmd *)&rcmd;
	eval_tree(cmd);
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

int	main(void)
{
	char		*line;

	// execution_test();
	while (1)
	{
		line = readline_dir(PROMPT);
		if (!line || !*line)
			break ;
		add_history(line);
		parse(line);
		free(line);
	}
	clear_history();
	return (0);
}

// static void	start_minishell(t_minishell m_shell)
// {
// 	handle_signal();
// 	while (1)
// 	{
// 		m_shell.line = readline_dir(PROMPT); //define PROMPT in minishell.h
// 		if (m_shell.line == NULL) //if ctrl + D
// 		{
// 			ft_printf("exit\n");
// 			ft_clean(m_shell, FALSE, TRUE);
// 			exit(EXIT_SUCCESS);
// 		}
// 		add_history(m_shell.line); //add to history
		
// 		//parse
// 		parse(m_shell.line); //parse the line
		
// 		//builtin
// 		m_shell.split_cmd = ft_split(m_shell.line, ' '); //split the cmd
// 		check_input(m_shell.split_cmd, m_shell); //check input
		
// 		ft_clean(m_shell, TRUE, FALSE);
// 	}
// 	ft_clean(m_shell, TRUE, TRUE);
// }

// int	main(int ac, char **av, char **envp)
// {
// 	t_minishell	m_shell;

// 	(void)av;
// 	(void)ac;
// 	// execution_test();
// 	ft_memset(&m_shell, 0, sizeof(t_minishell)); //set all to NULL/0
// 	m_shell.env_list = store_env(envp);
// 	start_minishell(m_shell);
// 	return (0);
// }