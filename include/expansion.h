/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:01:52 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/10/18 13:36:47 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

typedef enum e_string_type
{
	STR_NORM,
	STR_DQUOTE,
	STR_SQUOTE,
	STR_HEREDOC
}	t_str_type;

typedef enum e_expan_operation
{
	EOP_PARAM = 0b001,
	EOP_SPLIT = 0b010,
	EOP_QUOTE = 0b100,
}	t_exp_op;

typedef struct s_expansion_str
{
	char		*str;
	t_exp_op	op_flag;
}	t_exp_str;

/* main expansion function for commands */
char		**expand_argv_list(t_list **argv_list, t_minishell *m_shell);

/*-- Expansion Steps and a handler -- */
t_list		*expansion_handler(t_exp_str *exp_str, t_minishell *m_shell);
char		*parameter_expand(char *str, t_minishell *m_shell);
char		*quote_removal(char *str);

/* Utility functions */
t_exp_str	*make_new_expanstr(char *str, t_str_type type);
void		expand_mixed_string(t_list **result,
				char *str, t_minishell *m_shell);
t_list		*split_quotes(char *str);
char		*ft_str_replace(char *str, char *rep, char *with);
t_list		*join_expanded(t_list *lst);

/* Wildcard */
t_list		*expand_wildcard(char *str);
bool		is_match(char *pattern, char *str);

#endif
