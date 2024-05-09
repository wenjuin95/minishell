/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:54:27 by welow             #+#    #+#             */
/*   Updated: 2023/10/16 11:54:27 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

// #include <stdio.h>
// #include <strings.h> 
// int main() {
//     char buffer1[10];
// 	char buffer2[10];
//     // Use bzero to zero out the 'buffer1'.
//     bzero(buffer1, sizeof(buffer1));
// 	// use ft_bzero to zero out the 'buffer2'
// 	ft_bzero(buffer2, sizeof(buffer2));
//     // Print the contents of the 'buffer1'.
//     for (unsigned int i = 0; i <= sizeof(buffer1); i++) {
//         printf("buffer1[%d] = %d\n", i, buffer1[i]);
//     }
// 	// Print the contents of the 'buffer2'.
//     for (unsigned int i = 0; i <= sizeof(buffer2); i++) {
//         printf("buffer2[%d] = %d\n", i, buffer2[i]);
//     }
// }
