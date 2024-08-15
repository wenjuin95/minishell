/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:34:17 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/08/11 20:35:05 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Apply expansion for each chunk of string */
t_list	*apply_argv_expansion(t_list **list, t_minishell *m_shell)
{
	t_list	*curr;
	t_list	*result;
	t_list	*expanded;

	expanded = NULL;
	curr = *list;
	while (curr)
	{
		result = expansion_handler(curr->content, m_shell);
		ft_lstadd_back(&expanded, result);
		curr = curr->next;
	}
	return (expanded);
}

/*
split a single argv by its quotes (abc"bcd"'cde' -> abc, "bcd", 'cde')
apply expansions to the three different types
join all inputed argv back to one final argv array
*/
char	**expand_argv_list(t_list **argv_list, t_minishell *m_shell)
{
	t_list	*curr;
	t_list	*split_single;
	t_list	*expanded;
	t_list	*final_argv;

	final_argv = NULL;
	curr = *argv_list;
	while (curr)
	{
		split_single = split_quotes(curr->content);
		expanded = apply_argv_expansion(&split_single, m_shell);
		if (expanded)
			ft_lstadd_back(&final_argv, ft_lstnew_strjoin(expanded));
		curr = curr->next;
	}
	return (list_to_array(final_argv));
}
