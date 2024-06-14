/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:46:16 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/14 11:30:22 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "scanner.h"
# include "parser.h"

# include "builtin.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <termios.h>
# define TRUE 1
# define FALSE 0
# define PROMPT "\033[0;32mminishell>\033[0m " 
typedef struct s_minishell
{
	char	*line;
	char	**split_cmd;
	t_env_list	*env_list;
}	t_minishell;

//signal.c
void	handle_signal(void);

//utils.c
void	free_2d(char **str);
void	ft_clean_cmd(t_minishell m_shell);

#endif