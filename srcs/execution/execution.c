/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:26:24 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/08/16 23:47:15 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	eval_tree(t_cmd	*cmd, t_minishell *m_shell);

/*
*	@brief settup the redirections before executing the command
*	@param data the redirection data
*	@param m_shell the minishell struct
*	@return SUCCESS if "<<" not interrupt by SIGINT, FAIL 
			if interrupted by SIGINT
*/
int	setup_redirections(t_list *redir_list, t_minishell *m_shell)
{
	t_redir_data	*data;
	int				total_heredoc;
	int				current_heredoc;

	total_heredoc = num_heredoc(redir_list);
	current_heredoc = 1;
	while (redir_list != NULL)
	{
		data = (t_redir_data *)redir_list->content;
		if (data->type == TOK_DLESS)
		{
			if (set_here_doc(data, m_shell, current_heredoc, total_heredoc)
				== FAIL)
				return (FAIL);
			current_heredoc++;
		}
		else
		{
			set_fd(data);
		}
		redir_list = redir_list->next;
	}
	return (SUCCESS);
}

/*
*	@brief execute the command
*	@param command command to be executed
*	@param m_shell minishell struct
*	@note -normal command is in the "handle_new_minishell" function
*	@note -change_signal(true): child process signal
*	@note -change_signal(false): parent process signal
*/
void	command_execute(t_cmd *command, t_minishell *m_shell)
{
	t_exec_cmd	*e_cmd;
	char		**argv;
	int			status;

	e_cmd = (t_exec_cmd *)command;
	print_redirect(e_cmd->redir_list); //debug
	status = setup_redirections(e_cmd->redir_list, m_shell);
	m_shell->env_storage = convert_env_lst_to_env_array(m_shell->env_lst);
	argv = expand_argv_list(&e_cmd->argv_list, m_shell);
	if (check_input(argv[0]))
	{
		execute_input(m_shell, argv);
		reset_std_fds(m_shell);
	}
	else
	{
		change_shlvl(m_shell);
		handle_new_minishell(argv, m_shell, status);
	}
	change_signal(false);
	free_2d(argv);
}

/*
*	@brief do pipe command
*	@param cmd command to be executed
*	@param m_shell minishell struct
*	@note -ignore the signal when write and read from pipe
*	@note -when finish (false), change the signal back to default
*/
void	command_pipe(t_cmd *cmd, t_minishell *m_shell)
{
	t_pipe_cmd	*p_cmd;
	int			pipefd[2];

	p_cmd = (t_pipe_cmd *)cmd;
	print_pipe(p_cmd); //debug
	if (pipe(pipefd) == -1)
		perror_exit("pipe");
	create_left_child(pipefd, p_cmd->left_cmd, m_shell);
	create_right_child(pipefd, p_cmd->right_cmd, m_shell);
	close_pipes(pipefd);
	(waitpid(m_shell->pid, &m_shell->status, 0), get_exit_code(m_shell));
	(waitpid(m_shell->pid2, &m_shell->status, 0), get_exit_code(m_shell));
	change_signal(false);
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
	check_ast(m_shell);//debug
	eval_tree(m_shell->syntax_tree, m_shell);
	free_tree(m_shell->syntax_tree);
}
