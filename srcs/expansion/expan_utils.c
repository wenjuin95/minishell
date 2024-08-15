/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:41:46 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/08/11 20:38:46 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exp_str	*make_new_expanstr(char *str, t_str_type type)
{
	const t_exp_op	operation[] = {
	[STR_NORM] = EOP_PARAM | EOP_SPLIT,
	[STR_DQUOTE] = EOP_PARAM | EOP_QUOTE,
	[STR_SQUOTE] = EOP_QUOTE,
	};
	t_exp_str		*new;

	new = malloc(sizeof(t_exp_str));
	new->str = str;
	new->op_flag = operation[type];
	return (new);
}

static t_exp_str	*substr_match_quote(char *str, int *i, char quote)
{
	int			start;
	char		*sub_str;
	t_str_type	type;
	t_exp_str	*new_str;

	start = *i;
	(*i)++;
	while (str[*i] != quote)
		(*i)++;
	(*i)++;
	sub_str = ft_substr(str, start, *i - start);
	if (quote == '"')
		type = STR_DQUOTE;
	else
		type = STR_SQUOTE;
	new_str = make_new_expanstr(sub_str, type);
	return (new_str);
}

t_list	*split_quotes(char *str)
{
	t_list		*list;
	int			i;
	int			start;
	t_exp_str	*new_str;

	list = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			new_str = substr_match_quote(str, &i, str[i]);
		else
		{
			start = i;
			while (str[i] != '"' && str[i] != '\'' && str[i])
				i++;
			new_str = make_new_expanstr(ft_substr(str, start, i - start),
					STR_NORM);
		}
		ft_lstadd_back(&list, ft_lstnew(new_str));
	}
	return (list);
}

char	*ft_lststrjoin(t_list *lst)
{
	char	*str;
	t_list	*curr;
	size_t	total_len;

	total_len = 0;
	curr = lst;
	while (curr)
	{
		total_len += ft_strlen(curr->content);
		curr = curr->next;
	}
	str = ft_calloc(total_len + 1, sizeof(char));
	curr = lst;
	while (curr)
	{
		//printf("before: %s\t", curr->content);
		ft_strlcat(str, curr->content, total_len + 1);
		curr = curr->next;
	}
	//printf("joined: %s\n", str);
	return (str);
}

/* creates a new node after joining all strings of a list */
t_list	*ft_lstnew_strjoin(t_list *lst)
{
	char	*str;

	str = ft_lststrjoin(lst);
	return (ft_lstnew(str));
}
