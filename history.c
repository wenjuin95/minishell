/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:11:43 by welow             #+#    #+#             */
/*   Updated: 2024/05/09 19:48:59 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_history(char *input)
{
	int	fd;

	fd = open("./object_files/.history", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		printf("Error: file not found\n");
		exit(EXIT_FAILURE);
	}
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
	close(fd);
}

void	print_history(void)
{
	int		fd;
	char	*str;
	int		index;

	index = 0;
	fd = open("./object_files/.history", O_RDONLY);
	if (fd == -1)
	{
		printf("Error: file not found\n");
		exit(EXIT_FAILURE);
	}
	str = get_next_line(fd);
	while (str != NULL)
	{
		if (str[0] == '\n')
			continue ;
		printf("%d  %s", index, str);
		index++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
}
