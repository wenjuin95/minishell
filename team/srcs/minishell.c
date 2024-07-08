/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/08 17:50:47 by welow            ###   ########.fr       */
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

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_minishell	m_shell;

	(void)argc;
	(void)argv;
	ft_bzero(&m_shell, sizeof(t_minishell));
	while (1)
	{
		m_shell.env_storage = envp;
		store_env(&m_shell);
		line = readline_dir(PROMPT);
		if (!line || !*line)
			exit(0);
		add_history(line);
		m_shell.syntax_tree = parse(line);
		execute(&m_shell);
		free(line);
	}
}
