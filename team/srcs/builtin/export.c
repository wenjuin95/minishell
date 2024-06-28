/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:10:25 by welow             #+#    #+#             */
/*   Updated: 2024/06/28 15:57:10 by welow            ###   ########.fr       */
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

t_env_lst	*copy_node(t_env_lst *node)
{
	t_env_lst	*copy;

	copy = malloc(sizeof(t_env_lst));
	copy->name = strdup(node->name);
	if (node->value != NULL)
		copy->value = ft_strdup(node->value);
	else
		copy->value = NULL;
	copy->next = NULL;
	return (copy);
}

t_env_lst	*sorted_insert(t_env_lst *head, t_env_lst *node)
{
	t_env_lst	*current;

    if (!head || ft_strncmp(node->name, head->name, ft_strlen(node->name)) <= 0)
	{
        node->next = head;
        return node;
    }
    current = head;
    while (current->next && ft_strncmp(node->name, current->next->name, ft_strlen(node->name)) > 0)
	{
        current = current->next;
    }
    node->next = current->next;
    current->next = node;
    return head;
}

t_env_lst *sort_export(t_env_lst *head) 
{
	t_env_lst	*sorted;
	t_env_lst	*current;
	t_env_lst	*next;

	sorted = NULL;
	current = head;
    while (current)
	{
        next = current->next;
        sorted = sorted_insert(sorted, copy_node(current));
        current = next;
    }

    return sorted;
}

/*
*	@brief print all the environment variables with "declare -x"
*/
void	print_export(t_minishell *m_shell)
{
	t_env_lst	*cur;
	t_env_lst	*tmp;
	int			i;

	tmp = sort_export(m_shell->env_lst);
	cur = tmp;
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
*	@return true if the command is alphanumeric and underscore, false if not
*/
bool	check_alphanum(char *cmd)
{
	int	i;

	i = 1;
	if (ft_isalpha(cmd[0]) == 0 && cmd[0] != '_')
		return (false);
	while (cmd[i] && cmd[i] != '=')
	{
		if (ft_isalnum(cmd[i]) == 0 && cmd[i] != '_')
			return (false);
		i++;
	}
	return (true);
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
		if (check_alphanum(cmd[i]) == false)
			return (export_err_msg(cmd[i]));
		else
		{
			str = get_name(cmd[i]);
			if (check_name_exist(str, m_shell))
				(update_env(str, get_value(cmd[i]), false, m_shell), free(str));
			else
				(update_env(str, get_value(cmd[i]), true, m_shell), free(str));
		}
		i++;
	}
	return (0);
}
