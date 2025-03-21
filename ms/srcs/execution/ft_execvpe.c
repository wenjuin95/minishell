/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvpe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:31:08 by tkok-kea          #+#    #+#             */
/*   Updated: 2025/03/21 16:02:34 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief find the valid path for the executable file
*	@param paths array of paths to be checked
*	@param file the filename to be checked
*	@note 1. using access() to test all paths + filename combinations
*	@note 2. keeps note if one of the files exists but user has no permission
*			 to execute and sets errno accordingly
*/
char	*find_valid(char **paths, const char *file)
{
	char	*combined;

	while (*paths)
	{
		combined = ft_joinl("/", *paths, file, (char *) NULL);
		if (!combined)
		{
			free(combined);
			return (NULL);
		}
		if (access(combined, X_OK) == 0)
			return (combined);
		free(combined);
		paths++;
	}
	return (NULL);
}

/*
man execvpe
wrapper function for execve
v - argv is accepted in a form of an array of pointers;
as opposed to 'l' functions which are variadic functions for argv
p - looks for filename executable from the PATH environmental variable
if filename doesn't contain a '/' else it just uses the filename
'e' - uses specified envp
*/
void	ft_execvpe(const char *file, char *const argv[], char *const envp[])
{
	char	*path;
	char	**split_paths;
	char	*valid;

	path = ft_getenv("PATH", envp);
	if (!path)
		path = "";
	if (ft_strchr(file, '/'))
	{
		(execve(file, argv, envp), perror("execve"));
		return ;
	}
	split_paths = ft_split(path, ':');
	valid = find_valid(split_paths, file);
	free_2d(split_paths);
	if (valid)
	{
		execve(valid, argv, envp);
		free(valid);
	}
	else
	{
		ft_putstr_fd((char *)file, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
}
