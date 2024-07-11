/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:46:16 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/10 11:36:59 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includelibs.h"
# include "libft.h"
# include "scanner.h"
# include "parser.h"
# include "execution.h"
# include "builtin.h"

# define TRUE 1
# define FALSE 0
# define PROMPT "\033[1;32mminishell:\033[0m [" 
# define END_PROMPT "] \033[1;33m>\033[0m "

typedef struct s_minishell
{
	char			*line;
	t_cmd			*syntax_tree;
	int				std_fds[3];
	char			**split_cmd;
	int				exit_code;
	char			**env_storage;
	t_env_lst		*env_lst;
	t_list			*garbage;
	struct termios	ori_term;
	struct termios	new_term;
}	t_minishell;

typedef void	(*t_command)(t_cmd *, t_minishell *);

void	execute(t_minishell *m_shell);

//signal.c
void	handle_signal(t_minishell *minishell);

//utils.c
void	free_2d(char **str);
void	*to_gc_lst(void *content);
void	free_gc(void **content);
void	free_gc_lst(void);
void	ft_clean(t_minishell *m_shell, int clean_cmd);
void	free_2d(char **str);
void	*memory_manage(void *ptr, int clean);
void	ft_clean(t_minishell *m_shell, int clean_cmd);

// std fd saving and resetting

void	save_std_fds(t_minishell *m_shell);
void	reset_std_fds(t_minishell *m_shell);

void	perror_exit(const char *msg);
void	free_2d(char **str);
void	*memory_manage(void *ptr, int clean);
void	ft_clean(t_minishell *m_shell, int clean_cmd);

void	perror_exit(const char *msg);

#endif