/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:46:16 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/08/12 14:39:30 by welow            ###   ########.fr       */
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
# include "expansion.h"

# define PROMPT "\033[1;32mminishell:\033[0m [" 
# define END_PROMPT "] \033[1;33m>\033[0m "

typedef struct s_minishell
{
	t_cmd			*syntax_tree;
	int				std_fds[3];
	int				pid;
	int				pid2;
	int				status;
	int				exit_code;
	char			**env;
	char			**env_storage;
	t_env_lst		*env_lst;
	t_list			*garbage;
	struct termios	term;
}	t_minishell;

typedef void	(*t_command)(t_cmd *, t_minishell *);
typedef int		(*t_builtin)(t_minishell *, char **);

void	execute(t_minishell *m_shell);

//signal.c
void	handle_ctrl_c(int signum);
void	handle_child_signal(int signum);
void	handle_child_exit_signal(int signum);
void	change_signal(bool is_child);
void	mute_signal(t_minishell *m_shell);

//utils.c
void	free_2d(char **str);
void	clean_env_lst(t_env_lst *env_lst);
void	ft_clean(t_minishell *m_shell, int clean_cmd);
char	*ft_getenv(char *name, char *const envp[]);
char	**convert_env_lst_to_env_array(t_env_lst *env_lst);

//set_shlvl.c
char	**create_new_env(int pos, char *new_value, t_minishell *m_shell);
void	set_shlvl(t_minishell *m_shell, char *new_value);
void	change_shlvl(t_minishell *m_shell);

//gc_utils.c
void	*to_gc_lst(void *content);
void	free_gc(void **content);
void	free_gc_lst(void);

// std fd saving and resetting
void	save_std_fds(t_minishell *m_shell);
void	reset_std_fds(t_minishell *m_shell);

void	perror_exit(const char *msg);

#endif