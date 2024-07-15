/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dym_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:58:03 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/11 17:27:18 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief initialize a dynamic array
*	@return new dynamic array
*/
t_dym_arr	*dym_arr_init(void)
{
	t_dym_arr	*new_arr;

	new_arr = malloc(sizeof(t_dym_arr));
	new_arr->capacity = 0;
	new_arr->size = 0;
	new_arr->arr = NULL;
	return (new_arr);
}

/*
*	@brief add new string to the dynamic array
*	@param array: dynamic array to add to
*	@param new: new string to add
*/
void	add_to_array(t_dym_arr *array, const char *new)
{
	int		new_capacity;
	char	**new_array;

	if (array->capacity == 0)
	{
		array->capacity = 1;
		array->arr = malloc(sizeof(char *));
		if (array->arr == NULL)
			perror_exit("execve");
	}
	else if (array->size >= array->capacity)
	{
		new_capacity = array->capacity * 2;
		new_array = malloc(new_capacity * sizeof(char *));
		if (new_array == NULL)
			perror_exit("execve");
		ft_memmove(new_array, array->arr, (array->capacity * sizeof(char *)));
		free(array->arr);
		array->arr = new_array;
		array->capacity = new_capacity;
	}
	array->arr[array->size] = ft_strdup(new);
	array->size++;
}

/*
*	@breif add parsed redirection to the redirection list
*	@param redir_list: redirection link list
*	@param parser: parser
*/
void	add_to_redir_list(t_list **redir_list, t_parser *parser)
{
	t_redir_data	*new_data;

	new_data = malloc(sizeof(t_redir_data));
	new_data->type = parser->next_token.type;
	advance_psr(parser);
	if (parser->next_token.type == TOK_WORD)
	{
		new_data->value = ft_strdup(parser->next_token.value);
		ft_lstadd_back(redir_list, ft_lstnew((void *)new_data));
		advance_psr(parser);
	}
	else
		printf("Syntax Error near %s\n", parser->next_token.value);
}
