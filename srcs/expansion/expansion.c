/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:34:17 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/09/11 14:56:09 by welow            ###   ########.fr       */
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
	ft_lstclear(list, free);
	return (expanded);
}

/*
*	@brief split a string by quotes and return a linked list
*	@param str the string to be split
*	@return the linked list of splitted string
*	@note 1. split_quote: get the string and type into the linked list
*	@note 2. apply_argv_expansion: apply expansions to the types
*		     a. EOP_SPLIT: next word is space separated
*		     b. EOP_PARAM: next word is param/key value ?
*		     c. EOP_QUOTE: next word is quoted
*/
void	expand_mixed_string(t_list **result, char *str, t_minishell *m_shell)
{
	t_list	*split;
	t_list	*expanded;

	split = split_quotes(str);
	expanded = apply_argv_expansion(&split, m_shell);
	if (expanded)
		ft_lstadd_back(result, join_expanded(expanded));
}

/*
split a single argv by its quotes (abc"bcd"'cde' -> abc, "bcd", 'cde')
apply expansions to the three different types
join all inputed argv back to one final argv array
*/
char	**expand_argv_list(t_list **argv_list, t_minishell *m_shell)
{
	t_list	*curr;
	t_list	*final_argv;

	final_argv = NULL;
	curr = *argv_list;
	while (curr)
	{
		expand_mixed_string(&final_argv, curr->content, m_shell);
		curr = curr->next;
	}
	return (to_gc_lst(list_to_array(final_argv)));
}
