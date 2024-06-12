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

/*
*	@brief	check if the variable is valid
*	@param	cmd	argument to check
*	@return	0 if success, 1 if fail
*/
// static int	check_var(char **cmd)
// {
// 	int	i;

// 	i = 1;
// 	if (ft_isalpha(cmd[i][0]) == 0 || ft_strchr(cmd[i], '=') != NULL) //check for alpha or check for value in the env variable
// 	{
// 		printf("minishell: unset: `%s': not a valid identifier\n", cmd[i]);
// 		return (1);
// 	}
// 	return (0);
// }


// /*
// *	@brief	remove the environment variable
// *	@param	env_list	pointer to the link list
// *	@param	cmd			argument to check
// */
// void	unset_var(t_env_list *env_list, char *cmd)
// {
// 	t_env_list	*current;
// 	t_env_list	*prev;

// 	current = env_list;
// 	prev = NULL;
// 	while (current)
// 	{
// 		if (ft_strncmp(cmd, current->env_var, ft_strlen(current->env_var)) == 0) //compare the name of the env variable
// 		{
// 			if (prev)
// 				prev->next = current->next;
// 			else
// 				env_list = current->next;
// 			free(current->env_var);
// 			free(current);
// 			return ;
// 		}
// 		prev = current;
// 		current = current->next;
// 	}
// }

// /*
// *	@brief	handle unset command
// *	@param	env_list	pointer to the link list
// *	@param	cmd			argument to check
// *	@return	0 if success, 1 if fail
// */
// int	unset_option(t_env_list *env_list, char **cmd)
// {
// 	int	i;

// 	i = 1;
// 	while (cmd[i])
// 	{
// 		unset_var(env_list, cmd[i]);
// 		i++;
// 	}
// 	return (0);
// }

// int	remove_env_var(t_env_list *env_list, char *name)
// {
// 	t_env_list	*current;
// 	t_env_list	*prev;

// 	current = env_list;
// 	while(current)
// 	{
// 		if (ft_strncmp(name, current->env_var, ft_strlen(name)) == 0)
// 		{
// 			if (current->next == NULL)
// 				return (0);
// 			else
// 			{
// 				prev->next = current->next;
// 				free(current->env_var);
// 				free(current);
// 				return (0);
// 			}
// 		}
// 		else
// 		{
// 			prev = current;
// 			current = current->next;
// 		}
// 	}
// 	env_list = current;
// 	return (1);
// }

// int	unset_option(t_env_list *env_list, char **cmd)
// {
// 	int	i;

// 	i = 1;
// 	if (cmd[i] != NULL)
// 	{
// 		if(check_name_exist(env_list, cmd[i]) == TRUE)
// 		{
// 			remove_env_var(env_list, cmd[i]);
// 			return (0);
// 		}
// 	}
// 	return (1);
// }
