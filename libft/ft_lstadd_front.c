/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:59:07 by welow             #+#    #+#             */
/*   Updated: 2023/10/18 19:13:03 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new -> next = *lst;
	*lst = new;
}

// #include <stdio.h>
// #include <stdlib.h>

// typedef struct s_list {
//     void *content;
//     struct s_list *next;
// } t_list;

// t_list *ft_lstnew(void *content) {
//     t_list *new_node = (t_list *)malloc(sizeof(t_list));
//     if (new_node == NULL) {
//         return NULL;
//     }

//         new_node->content = content;
//         new_node->next = NULL;
//     return new_node;
// }

// int main() 
// {
//     int data1 = 42;
// 	int data2 = 123;
//     t_list *head = ft_lstnew(&data1);
// 	t_list *node2 = ft_lstnew(&data2);

// 	head -> next = node2;

//     int data4 = 100;
//     t_list *node4 = ft_lstnew(&data4);
//     ft_lstadd_front(&head, node4);

//     t_list *current = head;
// 	while (current)
// 	{
// 		int *value = (int *)(current->content);
// 		printf("Node content: %d\n", *value);
// 		current = current -> next;
// 	}

//     free(head);
// 	free(node2);

//     return 0;
// }
