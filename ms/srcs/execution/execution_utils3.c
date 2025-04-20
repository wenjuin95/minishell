/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:02:18 by welow             #+#    #+#             */
/*   Updated: 2024/08/24 16:09:58 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief strip the quotes from the delimiter
*	@param delim delimiter
*	@param quoted check if the delimiter is quoted
*	@return stripped delimiter
*	@note 1. if the delimiter is quoted, set quoted to true
*			 and send to expand the parameter
*	@note 2. if the delimiter is not quoted, copy the delimiter to the
			 stripped
*/
char	*strip_quotes(char *delim, bool *quoted)
{
	char	*stripped;
	char	*cptr;

	stripped = ft_calloc(ft_strlen(delim) + 1, 1);
	cptr = stripped;
	while (*delim)
	{
		if (*delim == '\'' || *delim == '"')
			*quoted = true;
		else
		{
			*cptr = *delim;
			cptr++;
		}
		delim++;
	}
	return (stripped);
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
int	handle_heredoc_parent(t_minishell *m_shell, int fds[])
{
	int	readfd;

	waitpid(m_shell->pid, &m_shell->status, 0);
	get_exit_code(m_shell);
	if (WIFEXITED(m_shell->status)
		&& WEXITSTATUS(m_shell->status) == EXIT_SUCCESS)
	{
		readfd = open(HEREDOC_TEMP, O_RDONLY);
		fds[STDIN_FILENO] = readfd;
		return (SUCCESS);
	}
	return (FAIL);
}

/*
*	@brief create a child process for here document
*	@param delimiter delimiter
*	@param quoted check if the delimiter is quoted
*	@param m_shell minishell struct
*	@note 1. if quoted is false means the delimiter is not quoted
*			 so we need to expand the parameter and write to the file
*/
void	handle_heredoc_child(char *delimiter, bool quoted, t_minishell *m_shell)
{
	int		writefd;
	char	*line;

	writefd = open(HEREDOC_TEMP,
			O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (writefd == -1)
		perror_exit("open");
	while (true)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, delimiter) == 0)
		{
			if (line == NULL)
				printf("minishell: warning: %s (wanted `%s')\n", ERRMSG_HEREDOC,
					delimiter);
			free(line);
			break ;
		}
		if (line[0] == '\n' && line[1] == '\0')
		{
			free(line);
			continue ;
		}
		if (quoted == false)
			line = parameter_expand(line, m_shell);
		ft_putendl_fd(line, writefd);
		free(line);
	}
	(close(writefd), ft_clean(m_shell));
	exit(EXIT_SUCCESS);
}

/*
*	@brief set the here document
*	@param delim delimiter
*	@param fds file descriptors
*	@param m_shell minishell struct
*	@return SUCCESS: if no interrupt by SIGINT, FAIL: if interrupted by SIGINT
*	@note 1. SIGINT terminate the child process and return FAIL
*	@note 2. after signal execute from child, the parent process will
*			 follow the child signal (prevent double print prompt)
*/
int	set_here_doc(char *delim, int fds[], t_minishell *m_shell)
{
	char	*delimiter;
	bool	quoted;

	m_shell->pid = fork();
	if (m_shell->pid == 0)
	{
		quoted = false;
		delimiter = strip_quotes(delim, &quoted);
		signal(SIGINT, SIG_DFL);
		handle_heredoc_child(delimiter, quoted, m_shell);
		ft_clean(m_shell);
		exit(SUCCESS);
	}
	else
	{
		signal(SIGINT, handle_child_signal);
		return (handle_heredoc_parent(m_shell, fds));
	}
}
