/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:57:42 by welow             #+#    #+#             */
/*   Updated: 2023/10/19 21:01:53 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// #include <stdio.h>
// #include <stdlib.h>

// // Define a simple linked list structure
// typedef struct s_list
// {
//     void *content;
//     struct s_list *next;
// } t_list;

// // Function to apply on each element of the list
// void apply_function(void *content)
// {
// Example: Print the content (you can replace this with your specific function)
//     printf("%s\n", (char *)content);
// }

// int main()
// {
//     // Create a linked list
//     t_list *first = malloc(sizeof(t_list));
//     t_list *second = malloc(sizeof(t_list));
//     t_list *third = malloc(sizeof(t_list));

//     first->content = "Hello";
//     second->content = "World";
//     third->content = "123";
//     first->next = second;
//     second->next = third;
//     third->next = NULL;

//     // Iterate through the list and apply the function
//     ft_lstiter(first, apply_function);

//     // Clean up memory (free nodes)
//     free(first);
//     free(second);
//     free(third);

//     return 0;
// }
