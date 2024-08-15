/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dym_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:58:03 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/08/12 14:26:52 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dym_arr	*dym_arr_init(void)
{
	t_dym_arr	*new_arr;

	new_arr = malloc(sizeof(t_dym_arr));
	new_arr->capacity = 0;
	new_arr->size = 0;
	new_arr->arr = NULL;
	return (new_arr);
}

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
