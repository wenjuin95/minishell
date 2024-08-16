/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:02:18 by welow             #+#    #+#             */
/*   Updated: 2024/08/14 18:02:18 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	num_heredoc(t_list *redir_list)
{
	t_redir_data	*data;
	int				size;

	size = 0;
	while (redir_list != NULL)
	{
		data = (t_redir_data *)redir_list->content;
		if (data->type == TOK_DLESS)
			size++;
		redir_list = redir_list->next;
	}
	return (size);
}

/* FOR DEBUG */
void print_pipe(t_pipe_cmd *p_cmd)
{
	if (p_cmd->left_cmd->type == CMD_PIPE)
		printf("%sleft command   : PIPE COMMAND%s\n", RED, RESET);
	else if (p_cmd->left_cmd->type == CMD_EXEC)
		printf("%sleft command   : EXEC COMAND%s\n", RED, RESET);

	if (p_cmd->right_cmd->type == CMD_PIPE)
		printf("%sright command   : PIPE COMMAND%s\n", RED, RESET);
	else if (p_cmd->right_cmd->type == CMD_EXEC)
		printf("%sright command   : EXEC COMAND%s\n", RED, RESET);
}

void print_redirect(t_list *redir_list)
{
	t_redir_data	*data;

	while (redir_list != NULL)
	{
		data = (t_redir_data *)redir_list->content;
		if (data->type == TOK_DLESS)
			printf("%sredirect token: <<%s\n", GREEN, RESET);
		else if (data->type == TOK_DGREAT)
			printf("%sredirect token: >>%s\n", GREEN, RESET);
		else if (data->type == TOK_GREAT)
			printf("%sredirect token: >%s\n", GREEN, RESET);
		else if (data->type == TOK_LESS)
			printf("%sredirect token: <%s\n", GREEN, RESET);
		else
			printf("%sredirect token: NULL%s\n", GREEN, RESET);
		printf("%sredirect value: %s%s\n", GREEN, data->value, RESET);
		redir_list = redir_list->next;
	}
}

void check_ast(t_minishell *m_shell)
{
	if (m_shell->syntax_tree->type == CMD_PIPE)
		printf("%sast   : PIPE COMMAND%s\n", YELLOW, RESET);
	else if (m_shell->syntax_tree->type == CMD_EXEC)
		printf("%sast   : EXEC COMAND%s\n", YELLOW, RESET);
}