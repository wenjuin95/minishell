/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:12:01 by welow             #+#    #+#             */
/*   Updated: 2024/06/10 13:17:46 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
*	@brief	sort the environment variable in alphabetical order
*	@param	env_list	pointer to the link list
*/
void	sort_env(t_env_list *env_list)
{
	t_env_list	*current;
	t_env_list	*next;
	char		*temp;

	current = env_list;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (ft_strncmp(current->env_var, next->env_var,
					ft_strlen(current->env_var)) > 0)
			{
				temp = current->env_var;
				current->env_var = next->env_var;
				next->env_var = temp;
			}
			next = next->next;
		}
		current = current->next;
	}
}

/*
*	@brief	check if the environment variable has value
*	@param	env_var	environment variable
*	@return	TRUE if has value, FALSE if not
*/
int check_env_value(char *env_var)
{
	char	*tmp;

	tmp = ft_strchr(env_var, '='); //return the value
	if (tmp != NULL && tmp[1] != '\0') //check if has value and next word is not '\0'
		return (TRUE);
	return (FALSE);
}

/*
*	@brief	check if the environment variable name exist in the link list
*	@param	env_list	pointer to the link list
*	@param	env_var		environment variable
*	@return	TRUE if exist, FALSE if not
*/
int	check_exist_name(t_env_list *env_list, char *env_var)
{
	t_env_list	*current;

	current = env_list;
	while (current)
	{
		if (ft_strncmp(current->env_name, env_var,
				ft_strlen(current->env_name)) == 0)
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}