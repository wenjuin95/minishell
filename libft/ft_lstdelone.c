/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:11:54 by welow             #+#    #+#             */
/*   Updated: 2023/10/20 22:11:21 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (del == NULL || lst == NULL)
		return ;
	(del)(lst -> content);
	free(lst);
}

// #include <stdlib.h>
// #include <stdio.h>

// typedef struct s_list {
//     void *content;
//     struct s_list *next;
// } t_list;

// void delete_content(void *content) {
//     free(content); // Example content deletion function
// }

// void ft_lstdelone(t_list *lst, void (*del)(void*)) {
//     if (!del)
//         return;
//     if (!lst)
//         return;
//     del(lst->content);
//     free(lst);
// }

// int main() {
//     t_list *node1 = malloc(sizeof(t_list));
//     node1->content = malloc(sizeof(int));
//     *((int*)node1->content) = 42; // Example content value for node1

//     t_list *node2 = malloc(sizeof(t_list));
//     node2->content = malloc(sizeof(int));
//     *((int*)node2->content) = 73; // Example content value for node2

//     t_list *node3 = malloc(sizeof(t_list));
//     node3->content = malloc(sizeof(int));
//     *((int*)node3->content) = 105; // Example content value for node3

//     // Linking the nodes together to form a list: node1 -> node2 -> node3
//     node1->next = node2;
//     node2->next = node3;
//     node3->next = NULL;

//     // Print the initial list
//     printf("Initial List:\n");
//     t_list *current = node1;
//     while (current != NULL) {
//         printf("Content: %d\n", *((int*)current->content));
//         current = current->next;
//     }

//     // Deleting the second node (node2) using ft_lstdelone
//     printf("\nAfter Removing Node2:\n");
//     ft_lstdelone(node2, delete_content);

//     // Relinking the list after removing node2
//     node1->next = node3;

//     // Print the list after removal
//     current = node1;
//     while (current != NULL) {
//         printf("Content: %d\n", *((int*)current->content));
//         current = current->next;
//     }

//     // Clean up the remaining nodes and free memory
//     ft_lstdelone(node1, delete_content);
//     ft_lstdelone(node3, delete_content);

//     return 0;
// }