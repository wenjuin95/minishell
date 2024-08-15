/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:06:19 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/08/11 20:44:45 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Applies expansion for exp_strs according to their ops_flag
*/
t_list	*expansion_handler(t_exp_str *exp_str, t_minishell *m_shell)
{
	t_list	*result;
	char	*res_str;

	result = NULL;
	res_str = ft_strdup(exp_str->str);
	if (exp_str->op_flag & EOP_PARAM)
		res_str = parameter_expand(res_str, m_shell);
	if (exp_str->op_flag & EOP_QUOTE)
		res_str = quote_removal(res_str);
	ft_lstadd_back(&result, ft_lstnew(res_str));
	return (result);
}
