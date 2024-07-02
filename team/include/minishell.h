/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:46:16 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/02 11:53:16 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includelibs.h"
# include "libft.h"
# include "scanner.h"
# include "parser.h"
# include "builtin.h"
# include "execution.h"

//window
# include <sys/types.h> //for t_mode
# include <sys/stat.h> //for s_mode

# define PROMPT "\033[1;32mminishell:\033[0m [" 
# define END_PROMPT "] \033[1;33m>\033[0m "

typedef struct s_minishell
{
	char		*line;
	char		**split_cmd;
	int			exit_code;
	char		**env_storage;
	t_env_lst	*env_lst;
}	t_minishell;

//signal.c
void	handle_signal(void);

//utils.c
void	free_2d(char **str);
void	*to_gc_lst(void *content);
void	free_gc(void **content);
void	free_gc_lst(void);
void	ft_clean(t_minishell *m_shell);

void	perror_exit(const char *msg);

#endif