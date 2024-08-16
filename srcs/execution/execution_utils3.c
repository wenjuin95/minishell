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

/*
*	@brief count the number of heredoc / "<<"
*	@param redir_list list of redirection data
*	@return number of heredoc
*/
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

/*
*	@brief parent process that read from the here document
*	@param m_shell minishell struct
*	@param final_heredoc check if it is the last heredoc
*	@return SUCCESS if the child process exit normally, FAIL if child 
*			interruped by SIGINT
*	@note 1. WIFEXITED: check if the child process exited normally
*	@note 2. WEXITSTATUS: get the exit status of the child process
*	@note (WINEXITED and WEXITSTATUS ,use together if not it will cause 
*	       undefined behavior)
*	@note 3. if the child process exit normally, cehck if is the last heredoc
*/
int	handle_heredoc_parent(t_minishell *m_shell, bool last_heredoc)
{
	int	readfd;

	waitpid(m_shell->pid, &m_shell->status, 0);
	get_exit_code(m_shell);
	if (WIFEXITED(m_shell->status)
		&& WEXITSTATUS(m_shell->status) == EXIT_SUCCESS)
	{
		if (last_heredoc)
		{
			readfd = open(HEREDOC_TEMP, O_RDONLY);
			dup2(readfd, STDIN_FILENO);
			close(readfd);
			unlink(HEREDOC_TEMP);
		}
		return (SUCCESS); //success
	}
	return (FAIL); //fail
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