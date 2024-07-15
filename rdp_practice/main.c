/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:01:33 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/13 21:40:30 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* practice using recursive descent parser to make a calculator */

#include "rdp.h"

void	error_msg(const char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("calculator > ");
		if (!line || !*line)
			exit(0);
		add_history(line);
		parse_into_ast(line);
		free(line);
	}
	return (0);
}
