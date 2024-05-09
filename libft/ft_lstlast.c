/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:31:38 by welow             #+#    #+#             */
/*   Updated: 2023/10/18 19:13:18 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	if (lst == NULL)
		return (NULL);
	last = lst;
	while (last -> next)
	{
		last = last -> next;
	}
	return (last);
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
//     int data2 = 65;
//     int data3 = 78;
//     t_list *head = ft_lstnew(&data1);
//     t_list *node2 = ft_lstnew(&data2);
//     t_list *node3 = ft_lstnew(&data3);

// 	head -> next = node2;
// 	node2 -> next = node3;

//     t_list *lastNode = ft_lstlast(head);
//     int *lastValue = (int *)(lastNode->content);
//     printf("Last Node content: %d\n", *lastValue);

//     free(head);
//     free(node2);
//     free(node3);

//     return 0;
// }