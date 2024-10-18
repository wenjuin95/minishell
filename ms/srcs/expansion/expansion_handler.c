/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:06:19 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/08/13 21:35:26 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*word_splitting(char *str)
{
	t_list	*result;
	int		i;
	int		start;
	char	*new_str;

	result = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' && str[i])
			i++;
		if (str[i])
		{
			start = i;
			while (str[i] != ' ' && str[i])
				i++;
			new_str = ft_substr(str, start, i - start);
			ft_lstadd_back(&result, ft_lstnew(new_str));
			if (str[i])
				ft_lstadd_back(&result, ft_lstnew(NULL));
		}
	}
	return (result);
}

/*
Applies expansion for exp_strs according to their ops_flag
*/
t_list	*expansion_handler(t_exp_str *exp_str, t_minishell *m_shell)
{
	t_list	*result;
	t_list	*temp;

	result = NULL;
	ft_lstadd_back(&result, ft_lstnew(ft_strdup(exp_str->str)));
	free(exp_str->str);
	if (exp_str->op_flag & EOP_PARAM)
		result->content = parameter_expand(result->content, m_shell);
	if (exp_str->op_flag & EOP_SPLIT)
	{
		temp = result;
		result = word_splitting(result->content);
		ft_lstclear(&temp, free);
	}
	if (exp_str->op_flag & EOP_QUOTE)
		result->content = quote_removal(result->content);
	return (result);
}
