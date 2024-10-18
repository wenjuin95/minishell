/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:31:13 by welow             #+#    #+#             */
/*   Updated: 2024/10/18 15:12:02 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
static char	*readline_dir(char *str, t_minishell *m_shell)
{
	char	*pwd;
	char	*prompt;
	char	*updated_prompt;
	char	*line;

	pwd = get_envlst_value("PWD", m_shell);
	prompt = ft_strjoin(str, pwd);
	updated_prompt = ft_strjoin(prompt, END_PROMPT);
	free(prompt);
	line = readline(updated_prompt);
	free(updated_prompt);
	return (line);
}

/*
*	@brief initialize the minishell
*	@param m_shell minishell structure
*	@param envp environment variable
*/
static void	init_shell(t_minishell *m_shell, char *envp[])
{
	ft_bzero(m_shell, sizeof(t_minishell));
	save_std_fds(m_shell);
	m_shell->env = envp;
	init_signal(m_shell);
	change_shlvl(m_shell);
	store_env(m_shell);
	remove_env_var(m_shell, "OLDPWD");
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_minishell	m_shell;

	((void)argc, (void)argv);
	init_shell(&m_shell, envp);
	while (1)
	{
		line = readline_dir(PROMPT, &m_shell);
		if (!line)
			(ft_printf("exit\n"), exit(m_shell.exit_code));
		if (!*line)
		{
			free(line);
			continue ;
		}
		add_history(line);
		m_shell.syntax_tree = parse(line, &m_shell);
		if (m_shell.syntax_tree != NULL)
			execute(&m_shell);
		free(line);
	}
	return (clear_history(), ft_clean(&m_shell), 0);
}
