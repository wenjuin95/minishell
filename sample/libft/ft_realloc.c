/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 00:52:38 by ychng             #+#    #+#             */
/*   Updated: 2024/03/03 01:42:36 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static size_t	determine_copy_size(size_t original_size, size_t new_size)
{
	size_t	copy_size;

	if (original_size < new_size)
		copy_size = original_size;
	else
		copy_size = new_size;
	return (copy_size);
}

// The reason I have a function to determine the copy size
// Is because, of how ft_memcpy works,
// It won't check for \0 or anything of that sorts,
// it only runs until the size you specify
// So it's crucial, that I only copy until the original data,
// rather than going out of bound
void	*ft_realloc(void *ptr, size_t original_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	copy_size = determine_copy_size(original_size, new_size);
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}
