/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:56:04 by welow             #+#    #+#             */
/*   Updated: 2023/10/16 11:56:04 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
/*
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = STDOUT_FILENO; // Use the standard output file descriptor (stdout)

    ft_putchar_fd('H', fd); // Write 'H' to stdout
    ft_putchar_fd('i', fd); // Write 'i' to stdout
    ft_putchar_fd('\n', fd); // Write a newline character to stdout

    return 0;
}*/
