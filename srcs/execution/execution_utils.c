/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:14:00 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/10/05 21:14:29 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>

/*
*	@brief close the pipe file descriptor
*/
void	close_pipes(int	*pipefd)
{
	close(pipefd[PIPE_RD]);
	close(pipefd[PIPE_WR]);
}

/*
*	@brief free the redirection data
*/
void	free_redir_data(void *ptr)
{
	t_redir_data	*data;

	data = (t_redir_data *)ptr;
	free(data->value);
	free(data);
}

/*
*	@brief expand the string in redirection and get the result (str)
*	@param str string for expand
*	@param m_shell minishell structure
*	@return expanded string
*	@note 1. expand_mixed_string will expand the string and store in linked list
*	@note 2. if is NULL, return NULL and print error message
*	@note 3. copy the expanded string that is stored in the linked list to
*			 result (str)
*/
char	*expand_redir(char *str, t_minishell *m_shell)
{
	char	*result;
	t_list	*expanded;

	expanded = NULL;
	expand_mixed_string(&expanded, str, m_shell);
	if (ft_lstsize(expanded) != 1)
	{
		ft_putendl_fd("Ambigious redirect", STDERR_FILENO);
		ft_lstclear(&expanded, free);
		return (NULL);
	}
	result = ft_strdup(expanded->content);
	ft_lstclear(&expanded, free);
	return (result);
}

/*
*	@brief set the file descriptor before the command is executed(pipe or exe)
*	@param data redirection data
*	@note 1. save the exit status to the minishell exit code for print exit code
*	@note 2. return value is for exit code not checking
*	@test: [ cat < end ] will get exit code 1 (done)
*	@test: [ cat < ] will return prompt get error and exit code
*		   is 2 with no leak (OTW)
*/
int	set_fd(t_redir_data *data, int fds[], t_minishell *m_shell)
{
	const t_open_info	info[] = {
	[TOK_LESS] = {STDIN_FILENO, O_RDONLY},
	[TOK_GREAT] = {STDOUT_FILENO, O_WRONLY | O_CREAT | O_TRUNC},
	[TOK_DGREAT] = {STDOUT_FILENO, O_WRONLY | O_CREAT | O_APPEND}
	};
	const mode_t		default_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int					fd;
	char				*filename;

	filename = expand_redir(data->value, m_shell);
	if (filename == NULL)
		return (m_shell->exit_code = FAIL);
	fd = open(filename, info[data->type].flag, default_perms);
	if (fd == -1)
	{
		ft_putstr_fd("open: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		perror(": ");
		free(filename);
		return (m_shell->exit_code = FAIL);
	}
	free(filename);
	fds[info[data->type].fd_to] = fd;
	return (m_shell->exit_code = SUCCESS);
}

/*
*	@brief convert the linked list to array
*/
char	**list_to_array(t_list *list)
{
	char	**array;
	int		i;
	t_list	*curr;

	array = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	if (!array)
		perror_exit("malloc");
	i = 0;
	curr = list;
	while (curr)
	{
		array[i] = to_gc_lst(ft_strdup(curr->content));
		curr = curr->next;
		i++;
	}
	array[i] = NULL;
	ft_lstclear(&list, free);
	return (array);
}
