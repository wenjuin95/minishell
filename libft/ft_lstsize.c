/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:21:37 by welow             #+#    #+#             */
/*   Updated: 2023/10/18 12:37:02 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}

// #include <stdio.h>
// #include <stdlib.h>

// // Define the t_list structure
// typedef struct s_list {
//     void *content;
//     struct s_list *next;
// } t_list;

// // Define the ft_lstnew function
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

// 	head->next = node2;
//     node2->next = node3;

//     int number = ft_lstsize(head);
//     printf("Number of nodes: %d\n", number);
//     // Free the memory for the nodes when done
//     free(head);
//     free(node2);
//     free(node3);

//     return 0;
// }