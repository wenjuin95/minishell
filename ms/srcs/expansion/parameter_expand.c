/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:11:31 by tkok-kea          #+#    #+#             */
/*   Updated: 2025/03/21 16:30:52 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_name(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/*
*	@brief add the key to the link list
*	@param keys link list of keys
*	@param str string to be expanded
*	@param i index of the string (position of the key)
*	@note 1. if the key is '?', add the key to the link list
*	@note 2. if the key is env name, add the key to the link list
*/
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

/*
*	@brief if found '$' the next character is a key and store to link list
*		   else increment the index
*/
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

/*
*	@brief get the value for the '?' key
*	@param key key to be searched
*	@param m_shell minishell struct
*	@return value for the key
*	@note if key is '?', return the exit code
*	@note if key is env name, return the value of the env name
*	@note if key is not found, return an empty string
*/
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

/*
*	@brief check if the stirng is a valid name and return the expanded
		   string
*	@param str string to be expanded
*	@param m_shell minishell struct
*	@return expanded string
*/
char	*parameter_expand(char *str, t_minishell *m_shell)
{
	t_list	*keys_list;
	t_list	*curr;
	char	*value;
	char	*result;
	char	*temp;

	keys_list = find_keys(str);
	if (keys_list == NULL)
		return (str);
	result = ft_strdup(str);
	free(str);
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
