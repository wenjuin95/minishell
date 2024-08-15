/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:11:31 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/31 20:27:49 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_name(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static void	add_key(t_list **keys, char *str, int *i)
{
	int		start;
	char	*new_key;

	new_key = NULL;
	start = *i;
	(*i)++;
	if (str[*i] == '?')
		new_key = ft_substr(str, start, *i - start + 1);
	else if (ft_isalpha(str[*i]) || str[*i] == '_')
	{
		while (str[*i] && is_valid_name(str[*i]))
			(*i)++;
		new_key = ft_substr(str, start, *i - start);
	}
	if (new_key)
		ft_lstadd_back(keys, ft_lstnew(new_key));
}

static t_list	*find_keys(char *str)
{
	t_list	*keys;
	int		i;

	keys = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			add_key(&keys, str, &i);
		else
			i++;
	}
	return (keys);
}

static char	*get_value_for_key(char *key, t_minishell *m_shell)
{
	char	*value;

	if (key[1] == '?')
		value = ft_itoa(m_shell->exit_code);
	else
		value = ft_strdup(ft_getenv(&key[1], m_shell->env_storage));
	if (!value)
		return (ft_strdup(""));
	return (value);
}

char	*parameter_expand(char *str, t_minishell *m_shell)
{
	t_list	*keys_list;
	t_list	*curr;
	char	*value;
	char	*result;
	char	*temp;

	keys_list = find_keys(str);
	if (keys_list == NULL)
		return (ft_strdup(str));
	result = ft_strdup(str);
	curr = keys_list;
	while (curr)
	{
		value = get_value_for_key(curr->content, m_shell);
		temp = ft_str_replace(result, curr->content, value);
		free(value);
		free(result);
		result = temp;
		curr = curr->next;
	}
	ft_lstclear(&keys_list, free);
	return (result);
}
