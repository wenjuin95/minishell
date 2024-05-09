/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:56:26 by welow             #+#    #+#             */
/*   Updated: 2023/10/16 11:56:26 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i])
	{
		i++;
	}
	write(fd, s, i);
}
/*
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = STDOUT_FILENO; // Use the standard output file descriptor (stdout)

    ft_putstr_fd("Hello, World!", fd); // Write the string to stdout

    return 0;
}*/
