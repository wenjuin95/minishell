/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:45:33 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/25 10:41:06 by welow            ###   ########.fr       */
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
			ft_clean(m_shell, FALSE);
			ft_printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		add_history(m_shell->line);
		//parse
		ft_printf("===========PARSE============\n");
		parse(m_shell->line);
		ft_printf("============================\n\n");
		//builtin
		m_shell->split_cmd = ft_split(m_shell->line, ' ');
		check_input(m_shell, m_shell->split_cmd);
		ft_clean(m_shell, TRUE);
	}
	ft_clean(m_shell, FALSE);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	m_shell;

	(void)av;
	(void)ac;
	// execution_test();
	ft_memset(&m_shell, 0, sizeof(t_minishell));
	m_shell.env_storage = envp;
	store_env(&m_shell);
	start_minishell(&m_shell);
	return (0);
}