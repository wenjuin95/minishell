/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:55:43 by welow             #+#    #+#             */
/*   Updated: 2023/10/20 16:01:54 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new -> content = content;
	new -> next = NULL;
	return (new);
}

// #include <stdio.h>
// #include <stdlib.h>

// typedef struct s_list {
//     void *content;
//     struct s_list *next;
// } t_list;

// int main() 
// {
//     int data1 = 42;
//     int data2 = 65;
//     int data3 = 78;
//     t_list *head = ft_lstnew(&data1);
//     t_list *node2 = ft_lstnew(&data2);
//     t_list *node3 = ft_lstnew(&data3);

// 	head -> next = node2;
// 	node2 -> next = node3;

// 	t_list *current = head;
//     while (current) {
//         int *value = (int *)(current->content);
//         printf("Node content: %d\n", *value);
//         current = current->next;
//     }

// 	free(head);
//     free(node2);
//     free(node3);

//     return 0;
// }