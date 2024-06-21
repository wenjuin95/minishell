/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:46:16 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/21 16:58:32 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

# include "execution.h"
# include "libft.h"
# include "scanner.h"
# include "parser.h"

# include "builtin.h"
# include <signal.h>
# define TRUE 1
# define FALSE 0
# define PROMPT "\033[1;32mminishell:\033[0m [" 
# define END_PROMPT "] \033[1;33m>\033[0m "

typedef struct s_minishell
{
	char	*line;
	char	**split_cmd;
	int		exit_code;
	t_env_list	*env_list;
}	t_minishell;

//signal.c
void	handle_signal(void);

//utils.c
void	free_2d(char **str);
void	ft_clean(t_minishell m_shell, int c_split, int c_env);

#endif