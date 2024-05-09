/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:52:01 by welow             #+#    #+#             */
/*   Updated: 2023/10/18 13:22:00 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node_back;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	node_back = *lst;
	while (node_back -> next)
	{
		node_back = node_back -> next;
	}
	node_back -> next = new;
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

// int main() {
//     // Create the first node with an integer value (for example)
//     int data1 = 42;
//     int data2 = 65;
//     int data3 = 78;
//     t_list *head = ft_lstnew(&data1);
//     t_list *node2 = ft_lstnew(&data2);
//     t_list *node3 = ft_lstnew(&data3);

//     head->next = node2;
//     node2->next = node3;

//     int data4 = 88;
//     t_list *node4 = ft_lstnew(&data4);
//     ft_lstadd_back(&head, node4);

//     t_list *current = head;
//     int *value = (int *)(current->content);
//     printf("Node content: %d\n", *value);

//     while (head != NULL) {
//         t_list *temp = head;
//         head = head->next;
//         free(temp);
//     }

//     return 0;
// }
