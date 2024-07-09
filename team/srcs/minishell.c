/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/09 13:27:39 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "execution.h"

void	perror_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
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

void	save_std_fds(t_minishell *m_shell)
{
	m_shell->std_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	m_shell->std_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
	m_shell->std_fds[STDERR_FILENO] = dup(STDERR_FILENO);
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_minishell	m_shell;

	(void)argc;
	(void)argv;
	ft_bzero(&m_shell, sizeof(t_minishell));
	save_std_fds(&m_shell);
	while (1)
	{
		handle_signal(&m_shell);
		m_shell.env_storage = envp;
		store_env(&m_shell);
		line = readline_dir(PROMPT);
		if (!line)
		{
			ft_printf("exit\n");
			exit(0);
		}
		add_history(line);
		m_shell.syntax_tree = parse(line);
		execute(&m_shell);
		free(line);
	}
}
