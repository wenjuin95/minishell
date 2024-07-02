/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:31:08 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/02 11:59:56 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
man getenv
goes through the environmentable variables (which are "name=value" pairs) 
and searches for a string with the requested name and returns the value
*/
char	*ft_getenv(char *name, char *const envp[])
{
	char	**e_ptr;
	int		len;

	if (!envp || !name)
		return (NULL);
	e_ptr = (char **)envp;
	len = ft_strlen(name);
	while (*e_ptr)
	{
		if (ft_strnstr(*e_ptr, name, len))
			return (*e_ptr + len + 1);
		e_ptr++;
	}
	return (name);
}

/*
using access() to test all paths + filename combinations
keeps note if one of the files exists but user has no permission to execute
and sets errno accordingly
*/
char	*find_valid(char **paths, const char *file)
{
	char	**p_ptr;
	char	*path;
	char	*valid;

	p_ptr = paths;
	while (*p_ptr)
	{
		path = ft_strjoin(*p_ptr, "/");
		valid = ft_strjoin(path, file);
		free(path);
		if (!access(valid, X_OK))
			return (valid);
		free(valid);
		p_ptr++;
	}
	return (NULL);
}

void	free_split(char **strs)
{
	char	**s_ptr;

	s_ptr = strs;
	while (*strs)
	{
		free(*strs);
		strs++;
	}
	free(s_ptr);
}

/*
man execvp
wrapper function for execve
v - argv is accepted in a form of an array of pointers;
as opposed to 'l' functions which are variadic functions for argv
p - looks for filename executable from the PATH environmental variable
if filename doesn't contain a '/' else it just uses the filename
not 'e' - uses environ for execve call instead of specified envp
*/
void	ft_execvp(const char *file, char *const argv[], char *const envp[])
{
	char	*path;
	char	**split_paths;
	char	*valid;

	path = ft_getenv("PATH", envp);
	if (!path)
		path = "/bin:/usr/bin";
	if (ft_strchr(file, '/'))
	{
		execve(file, argv, envp);
		perror("execve");
		return ;
	}
	split_paths = ft_split(path, ':');
	valid = find_valid(split_paths, file);
	free_split(split_paths);
	if (valid)
		execve(valid, argv, envp);
	else
		ft_putendl_fd("command not found", STDERR_FILENO);
}
