/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:10:25 by welow             #+#    #+#             */
/*   Updated: 2024/06/24 15:33:52 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//function to print all the environment variables with "declare -x"
/*
* TODO:
* 0. create a export list
* 1. print all env after "declare -x"
* 2. must be sorted
* 3. new variable will go to the export list
* 4. export AAA=abc -> env_storage
* 5. export -> print all env in export list
* 6. export AAA -> export_storage
*/

/*
*	@brief print all the environment variables with "declare -x"
*/
void	print_export(t_minishell *m_shell)
{
	t_env_lst	*cur;
	int			i;

	cur = m_shell->env_lst;
	while (cur)
	{
		if (cur->value != NULL && (ft_strncmp(cur->name, "_", 2) != 0))
		{
			ft_printf("declare -x %s=", cur->name);
			i = 0;
			while ((cur->value)[i])
			{
				ft_printf("%c", (cur->value)[i++]);
			}
			ft_printf("\n");
		}
		else if (cur->value == NULL && (ft_strncmp(cur->name, "_", 2) != 0))
			ft_printf("declare -x %s\n", cur->name);
		cur = cur->next;
	}
}

/*
*	@brief check if the command is alphanumeric and underscore
*	@param cmd argument to be checked
*	@return TRUE if the command is alphanumeric and underscore, FALSE if not
*/
int	check_alphanum(char *cmd)
{
	int	i;

	i = 1;
	if (ft_isalpha(cmd[0]) == 0 && cmd[0] != '_')
		return (FALSE);
	while (cmd[i] && cmd[i] != '=')
	{
		if (ft_isalnum(cmd[i]) == 0 && cmd[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/*
*	@brief check name in env_lst
*	@param name name to be checked
*	@return TRUE if the name exist, FALSE if not
*/
int	check_name_exist(char *name, t_minishell *m_shell)
{
	t_env_lst	*current;

	current = m_shell->env_lst;
	while (current)
	{
		if (ft_strncmp(current->name, name, ft_strlen(name)) == 0)
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}

static int	export_err_msg(char *cmd)
{
	ft_printf("minishell: export: `%s': not a valid identifier\n", cmd);
	return (1);
}

int	export_option(t_minishell *m_shell, char **cmd)
{
	int		i;
	char	*str;

	i = 1;
	if (cmd[1] == NULL)
		return (print_export(m_shell), 0);
	while (cmd[i])
	{
		if (check_alphanum(cmd[i]) == FALSE)
			return (export_err_msg(cmd[i]));
		else
		{
			str = get_name(cmd[i]);
			if (check_name_exist(str, m_shell))
			{
				(update_env(str, get_value(cmd[i]), FALSE, m_shell), free(str));
			}
			else
			{
				(update_env(str, get_value(cmd[i]), TRUE, m_shell), free(str));
			}
		}
		i++;
	}
	return (0);
}
