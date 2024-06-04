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

int unset_option(t_env_list *env_list, char **cmd)
{
	t_env_list	*current;
	t_env_list	*prev;
	int			i;
	
	i = 1;
	while (cmd[i])
	{
		if (ft_isalpha(cmd[i][0]) == 0 || ft_strchr(cmd[i], '=') != NULL) //check for alpha or check for value in the env variable
		{
			printf("minishell: unset: `%s': not a valid identifier\n", cmd[i]);
			return (1);
		}
		else
		{
			current = env_list;
			prev = NULL;
			while (current)
			{
				if (ft_strncmp(current->env_var, cmd[i], ft_strlen(cmd[i])) == 0)
				{
					if (prev)
						prev->next = current->next;
					else
						env_list = current->next;
					free(current->env_var);
					free(current);
					break ;
				}
				prev = current;
				current = current->next;
			}
			return (0);
		}
		i++;
	}
	return (0);
}