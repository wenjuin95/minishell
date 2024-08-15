/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:26:24 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/08/15 18:15:44 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	eval_tree(t_cmd	*cmd, t_minishell *m_shell);

/*
*	@brief before execute if found "<<", then set "here_doc". If not "set_fd"
*	@param data the redirection data
*	@param m_shell the minishell struct
*/
void	setup_redirections(t_list *redir_list, t_minishell *m_shell)
{
	t_redir_data	*data;
	int				total_heredoc;
	int				current_heredoc;

	total_heredoc = num_heredoc(redir_list);
	current_heredoc = 0;
	while (redir_list != NULL)
	{
		data = (t_redir_data *)redir_list->content;
		if (data->type == TOK_DLESS)
		{
			set_here_doc(data, m_shell, current_heredoc, total_heredoc);
			current_heredoc++;
		}
		else
		{
			set_fd(data);
		}
		redir_list = redir_list->next;
	}
}

/*
*	@brief execute the command
*	@param command command to be executed
*	@param m_shell minishell struct
*	@note -normal command is in the "handle_new_minishell" function
*	@note -change_signal(true): change the signal for child process
*/
void	command_execute(t_cmd *command, t_minishell *m_shell)
{
	t_exec_cmd	*e_cmd;
	char		**argv;

	e_cmd = (t_exec_cmd *)command;
	setup_redirections(e_cmd->redir_list, m_shell);
	m_shell->env_storage = convert_env_lst_to_env_array(m_shell->env_lst);
	argv = expand_argv_list(&e_cmd->argv_list, m_shell);
	if (check_input(argv[0]))
	{
		change_signal(true);
		execute_input(m_shell, argv);
		reset_std_fds(m_shell);
	}
	else
	{
		change_shlvl(m_shell);
		handle_new_minishell(argv, m_shell);
	}
	free_2d(argv);
}

/*
*	@brief do pipe command
*	@param cmd command to be executed
*	@param m_shell minishell struct
*	@note -ignore the signal when write and read from pipe
*/
void	command_pipe(t_cmd *cmd, t_minishell *m_shell)
{
	t_pipe_cmd	*p_cmd;
	int			pipefd[2];

	p_cmd = (t_pipe_cmd *)cmd;
	if (pipe(pipefd) == -1)
		perror_exit("pipe");
	create_left_child(pipefd, p_cmd->left_cmd, m_shell);
	create_right_child(pipefd, p_cmd->right_cmd, m_shell);
	close_pipes(pipefd);
	(waitpid(m_shell->pid, &m_shell->status, 0), get_exit_code(m_shell));
	(waitpid(m_shell->pid2, &m_shell->status, 0), get_exit_code(m_shell));
}

/*
*	@brief 1. contains an lookup table(array) of functions
*	@brief 2. to execute when eval_tree() is called for a syntax tree node
*/
void	eval_tree(t_cmd	*cmd, t_minishell *m_shell)
{
	const t_command	commands[] = {
	[CMD_EXEC] = command_execute,
	[CMD_PIPE] = command_pipe,
	};

	if (!cmd)
		return ;
	commands[cmd->type](cmd, m_shell);
}

void	execute(t_minishell *m_shell)
{
	eval_tree(m_shell->syntax_tree, m_shell);
	free_tree(m_shell->syntax_tree);
}
