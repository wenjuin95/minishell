/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:07:35 by welow             #+#    #+#             */
/*   Updated: 2024/05/30 18:07:35 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char **unset_option(char **env_storage, char **cmd)
// {
// 	int	i;
// 	int	position;

// 	i = 1;
// 	while (cmd[i])
// 	{
// 		if (ft_isalpha(cmd[i][0]) == 0 || ft_strchr(cmd[i], '=') != NULL) //check for alpha or check for value in the env variable
// 		{
// 			printf("minishell: unset: `%s': not a valid identifier\n", cmd[i]);
// 			return (env_storage);
// 		}
// 		else
// 		{
// 			position = env_position(env_storage, cmd[i]); //get the position for remove
// 			if (position != -1)
// 				remove_env(env_storage, cmd[i]);
// 		}
// 		i++;
// 	}
// 	return (env_storage);
// }

//function to check the variable is valid
static int	check_var(char **cmd)
{
	int	i;

	i = 1;
	if (ft_isalpha(cmd[i][0]) == 0 || ft_strchr(cmd[i], '=') != NULL) //check for alpha or check for value in the env variable
	{
		printf("minishell: unset: `%s': not a valid identifier\n", cmd[i]);
		return (1);
	}
	return (0);
}

//function to remove the variable if found
void	unset_var(t_env_list *env_list, char *cmd)
{
	t_env_list	*current;
	t_env_list	*prev;

	current = env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(cmd, current->env_name, ft_strlen(current->env_name)) == 0) //compare the name of the env variable
		{
			if (prev)
				prev->next = current->next;
			else
				env_list = current->next;
			free(current->env_var);
			free(current->env_name);
			free(current->env_value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

//function to handle the unset command
int	unset_option(t_env_list *env_list, char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (check_var(cmd))
			return (1);
		else
			unset_var(env_list, cmd[i]);
		i++;
	}
	return (0);
}
