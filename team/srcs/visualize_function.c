#include "minishell.h"

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
		ft_printf("\033[1;33m===========PARSE==============\033[0m\n");
		parse(m_shell->line);
		if (m_shell->line != NULL)
			ft_printf("\033[1;33m==============================\033[0m\n");
		ft_printf("\n");
		m_shell->split_cmd = ft_split(m_shell->line, ' ');
		if (check_input(*m_shell->split_cmd) == true)
		{
			ft_printf("\033[1;33m===========BUILT-IN===========\033[0m\n");
			execute_input(m_shell, m_shell->split_cmd);
			if (m_shell->line != NULL)
				ft_printf("\033[1;33m==============================\033[0m\n");)
			ft_printf("\n");
		}
		else
		{
			ft_printf("\033[1;33m===========EXECUTION==========\033[0m\n");
			execution_test(m_shell->split_cmd, true);
			if (m_shell->line != NULL)
				ft_printf("\033[1;33m==============================\033[0m\n");
			ft_printf("\n");
		}
		free_2d(m_shell->split_cmd);
		free(m_shell->line); //for new command
	}
	ft_clean(m_shell);
}