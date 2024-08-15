/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:59:53 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/08/14 22:16:32 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define HEREDOC_TEMP "/tmp/minishell_heredoc_temp"
# define ERRMSG_HEREDOC "heredoc delimited by end-of-file"

typedef struct s_minishell	t_minishell;

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

/* Exec Utils */
void	close_pipes(int	*pipefd);
void	free_redir_data(void *ptr);
void	set_fd(t_redir_data *data);
void	set_here_doc(t_redir_data *data, t_minishell *m_shell,
			int c_h, int t_h);
char	**list_to_array(t_list *list);

/* Exec Utils 2 */
void	create_left_child(int pipefd[2], t_cmd *cmd, t_minishell *m_shell);
void	create_right_child(int pipefd[2], t_cmd *cmd, t_minishell *m_shell);
void	create_here_doc_child(t_redir_data *data);
void	get_exit_code(t_minishell *m_shell);
void	handle_new_minishell(char **argv, t_minishell *m_shell);

/* Exec Util 3 */
int		num_heredoc(t_list *redir_list);

#endif
