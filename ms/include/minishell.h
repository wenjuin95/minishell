/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:46:16 by tkok-kea          #+#    #+#             */
/*   Updated: 2025/03/19 16:24:50 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includelibs.h"
# include "libft.h"
# include "builtin.h"
# include "scanner.h"
# include "parser.h"
# include "execution.h"
# include "expansion.h"

# define PROMPT "\033[1;32mminishell:\033[0m ["
# define END_PROMPT "] \033[1;33m>\033[0m "

# define CTRL_SLASH 131
# define CTRL_C 130
# define GENERAL_ERROR 2
# define COMMAND_NOT_FOUND 127
# define NOT_DIGIT 255
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define HEREDOC_TEMP "/tmp/minishell_heredoc_temp"
# define ERRMSG_HEREDOC "heredoc delimited by end-of-file"
# define SUCCESS 0
# define FAIL 1

//bring the global variable to the header file for anywhere access
extern int		g_sig_exit_for_ctrl_c;

typedef struct s_minishell
{
	t_cmd			*syntax_tree;
	int				std_fds[3];
	int				pid;
	int				pid_left;
	int				pid_right;
	int				status;
	int				exit_code;
	char			**env;
	char			**env_storage;
	t_env_lst		*env_lst;
	t_list			*garbage;
	t_exec_cmd		*e_cmd;
	struct termios	term;
}	t_minishell;

typedef void	(*t_command)(t_cmd *, t_minishell *);
typedef int		(*t_builtin)(t_minishell *, char **);

void	execute(t_minishell *m_shell);

//signal.c
void	handle_main_signal(int signum);
void	handle_child_signal(int signum);
void	handle_child_exit_signal(int signum);
void	change_signal(bool is_child);
void	init_signal(t_minishell *m_shell);

//utils.c
void	free_2d(char **str);
void	clean_env_lst(t_env_lst *env_lst);
void	ft_clean(t_minishell *m_shell);

//env_utils2.c
char	*ft_getenv(char *name, char *const envp[]);
char	**convert_env_lst_to_env_array(t_env_lst *env_lst);
void	update_path(t_minishell *m_shell, char *locate);

//set_shlvl.c
void	update_shlvl(t_minishell *m_shell, char *new_value);
void	change_shlvl(t_minishell *m_shell);

//gc_utils.c
void	*to_gc_lst(void *content);
void	free_gc_lst(void);

// std fd saving and resetting
void	save_std_fds(t_minishell *m_shell);
void	reset_std_fds(t_minishell *m_shell);

void	perror_exit(const char *msg);

#endif
