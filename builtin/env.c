/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:32:25 by welow             #+#    #+#             */
/*   Updated: 2024/05/17 16:32:25 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	TODO:
 *	1. env
 *	2. env [any argument]
 */

/*
*	@brief store the environment variable to link list
*	@param envp	:: environment variable
*/
t_env_list	*store_env(char **envp)
{
	t_env_list	*env_list;
	t_env_list	*new;
	int			i;

	env_list = NULL;
	i = -1;
	while (envp[++i])
	{
		new = malloc(sizeof(t_env_list));
		if (new == NULL)
			return (NULL);
		new->env_var = ft_strdup(envp[i]);
		new->next = env_list;
		env_list = new;
	}
	return (env_list);
}

/*
*	@brief print the env variable
*	@param env_list	:: pointer to the link list
*/
void print_env(t_env_list *env_list)
{
	t_env_list	*tmp;

	tmp = env_list;
	while (tmp)
	{
		ft_printf("%s\n", tmp->env_var);
		tmp = tmp->next;
	}
}

/*
*	@brief clear the link list
*	@param env_list	:: pointer to the link list
*/
void clear_env_list(t_env_list *env_list)
{
	t_env_list	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp->env_var);
		free(tmp);
	}
}

/*
*	@brief handle env command
*	@param env_list :: pointer to the link list
*	@param cmd :: argument
*	@return	0 if success, 1 if error
*/
int	env_option(t_env_list *env_list, char **cmd)
{
	int	i;

	i = 1;
	if (cmd[i] == NULL)
	{
		print_env(env_list);
		return (0);
	}
	else
	{
		ft_printf("env: %s: No such file or directory\n", cmd[i]);
		return (1);
	}
}
