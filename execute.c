/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:15:43 by welow             #+#    #+#             */
/*   Updated: 2024/05/20 17:15:43 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_path(char **cmd, char**env_storage)
{
	char *full_path;
	char **path_split;
	char *command_path;
	int  i;

	if (access(*cmd, F_OK) == 0)
		return (*cmd);
	i = -1;
	while (ft_strncmp("PATH", *env_storage, 4) != 0)
		env_storage++;
	path_split = ft_split(*env_storage + 5, ':');
	i = -1;
	while (path_split[++i] != NULL)
	{
		command_path = ft_strjoin(path_split[i], "/");
		full_path = ft_strjoin(command_path, *cmd);
		free(command_path);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
	}
	free_2d(path_split);
	return (NULL);
}

void execute_cmd(char *input, char **env_storage)
{
	char *path;
	char **cmd;

	cmd = ft_split(input, ' ');
	path = get_path(cmd, env_storage);
	if (path == NULL)
	{
		/*debug use*/
		// printf("Command not found \n");
		return ;
	}
	if (execve(path, cmd, env_storage) == -1)
	{
		printf("Error: Command not found\n");
	}
	free_2d(cmd);
	free(path);
}
