/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:16:04 by welow             #+#    #+#             */
/*   Updated: 2024/07/01 13:16:04 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	@brief copy node from env_lst
*	@param node :: env_lst node
*	@return copied node
*/
static t_env_lst	*copy_node(t_env_lst *node)
{
	t_env_lst	*new_node;

	new_node = malloc(sizeof(t_env_lst));
	if (new_node == NULL)
		return (NULL);
	new_node->name = ft_strdup(node->name);
	new_node->value = ft_strdup(node->value);
	new_node->next = NULL;
	return (new_node);
}

/*
*	@brief swap the node
*	@param a :: node a
*	@param a_next :: node a->next
*/
static void	ft_swap_lst(t_env_lst *a, t_env_lst *a_next)
{
	char	*temp_name;
	char	*temp_value;

	temp_name = a->name;
	temp_value = a->value;
	a->name = a_next->name;
	a->value = a_next->value;
	a_next->name = temp_name;
	a_next->value = temp_value;
}

/*
*	@brief append copy node to the copied list
*	@param head :: head of copied list
*	@return copied list
*/
t_env_lst	*copy_list(t_env_lst *head)
{
	t_env_lst	tmp_head;
	t_env_lst	*current;

	current = &tmp_head;
	tmp_head.next = NULL;
	while (head)
	{
		current->next = copy_node(head);
		current = current->next;
		head = head->next;
	}
	return (tmp_head.next);
}

/*
*	@brief sort the list in alphabetical order
*	@param head :: head of the copy list
*/
void	sort_list(t_env_lst **head)
{
	int			swapped;
	t_env_lst	*current;
	t_env_lst	*tmp;

	swapped = 1;
	tmp = NULL;
	if (head == NULL)
		return ;
	while (swapped != 0)
	{
		swapped = 0;
		current = *head;
		while (current->next != tmp)
		{
			if (ft_strncmp(current->name, current->next->name,
					ft_strlen(current->name)) > 0)
			{
				ft_swap_lst(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		tmp = current;
	}
}

/*
*	@brief free the copied list
*	@param head :: head of the copied list
*/
void	free_copy(t_env_lst *head)
{
	t_env_lst	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->name);
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}
