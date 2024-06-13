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

#include "../minishell.h"

/*
 *	handle env command
 *	1. env
 */

// /*
// *	@brief store the environment variable to link list
// *	@param envp	environment variable
// *	@return	pointer to the link list
// *	@note memory need to free
// */
// t_env_list	*store_env(char **envp)
// {
// 	t_env_list	*env_list;
// 	t_env_list	*new;
// 	int			i;

// 	env_list = NULL;
// 	i = -1;
// 	while (envp[++i])
// 	{
// 		new = malloc(sizeof(t_env_list));
// 		if (new == NULL)
// 			exit(EXIT_FAILURE);
// 		new->env_var = ft_strdup(envp[i]);
// 		new->env_name = get_env_name(envp[i]);
// 		new->env_value = get_env_value(new->env_var, new->env_name);
// 		new->next = env_list;
// 		env_list = new;
// 	}
// 	return (env_list);
// }

// /*
// *	@brief print the environment variable
// *	@param env_list	pointer to the link list
// */
// void print_env(t_env_list *env_list)
// {
// 	t_env_list	*tmp;

// 	tmp = env_list;
// 	while (tmp)
// 	{
// 		ft_printf("%s\n", tmp->env_var);
// 		// ft_printf("name: %s\n", tmp->env_name); //debug
// 		// ft_printf("value: %s\n\n", tmp->env_value); //debug
// 		tmp = tmp->next;
// 	}
// }

// /*
// *	@brief clear the environment link list
// *	@param env_list	pointer to the link list
// */
// void clear_env_list(t_env_list *env_list)
// {
// 	t_env_list	*tmp;

// 	while (env_list)
// 	{
// 		tmp = env_list;
// 		env_list = env_list->next;
// 		free(tmp->env_var);
// 		free(tmp->env_name);
// 		free(tmp->env_value);
// 		free(tmp);
// 	}
// }

// /*
// *	@brief get the value from env variable
// *	@param env_var	environment variable
// *	@param name		name of the env variable
// *	@return	value of the env variable
// *	@note memory need to free
// */
// char *get_env_value(char *env_var, char *name)
// {
// 	int		i;
// 	char	*value;

// 	if (ft_strncmp(env_var, name, ft_strlen(env_var)) == 0) //handle if no value 
// 		return (value = ft_strdup(""));
// 	i = ft_strlen(name) + 1; //get the length of the name with "="
// 	value = ft_strdup(env_var + i); //get the value of the env variable
// 	if (value == NULL)
// 		return (NULL);
// 	return (value);
// }

// /*
// *	@brief get the name from env variable
// *	@param env_var	environment variable
// *	@return	name of the env variable
// *	@note memory need to free
// */
// char	*get_env_name(char *env_var)
// {
// 	char *name;
// 	int i;

// 	i = 0;
// 	while (env_var[i] != '=')
// 		i++;
// 	ft_printf("i: %d\n", i); //debug
// 	name = ft_substr(env_var, 0, i);
// 	return (name);
// }

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
