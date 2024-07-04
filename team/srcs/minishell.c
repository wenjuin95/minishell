/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:45:33 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/28 15:10:57 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

void	perror_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

/*
* 	@brief	modi the prompt to include the directory
*	@param 	str		prompt name
*	@return	prompt name with directory
*/
static char	*readline_dir(char *str)
{
	char	*pwd;
	char	*prompt;
	char	*updated_prompt;
	char	*line;

	pwd = getcwd(NULL, 0);
	prompt = ft_strjoin(str, pwd);
	free(pwd);
	updated_prompt = ft_strjoin(prompt, END_PROMPT);
	free(prompt);
	line = readline(updated_prompt);
	free(updated_prompt);
	return (line);
}

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline_dir(PROMPT);
		if (!line || !*line)
			exit(0);
		add_history(line);
		parse(line);
		free(line);
	}
}
