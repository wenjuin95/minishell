/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:59:53 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/10/18 13:39:37 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

enum e_pipefd
{
	PIPE_RD = 0,
	PIPE_WR = 1
};

typedef struct s_open_info
{
	int	fd_to;
	int	flag;
}	t_open_info;

void	ft_execvpe(const char *file, char *const argv[], char *const envp[]);
void	eval_tree(t_cmd	*cmd, t_minishell *m_shell);
void	command_list(t_cmd *cmd, t_minishell *m_shell);
void	command_subshell(t_cmd *cmd, t_minishell *m_shell);

/* Exec Utils */
void	close_pipes(int	*pipefd);
void	free_redir_data(void *ptr);
int		set_fd(t_redir_data *data, int fds[], t_minishell *m_shell);
char	**list_to_array(t_list *list);

/* Exec Utils 2 */
void	create_left_child(int pipefd[2], t_cmd *cmd, t_minishell *m_shell);
void	create_right_child(int pipefd[2], t_cmd *cmd, t_minishell *m_shell);
void	get_exit_code(t_minishell *m_shell);
void	handle_execution(char **argv, t_minishell *m_shell, int status);

/* Exec Util 3 */
int		handle_heredoc_parent(t_minishell *m_shell, int fds[]);
void	handle_heredoc_child(char *delimiter, bool quoted,
			t_minishell *m_shell);
int		set_here_doc(char *delim, int fds[], t_minishell *m_shell);

#endif
