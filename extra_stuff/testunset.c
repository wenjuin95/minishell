#include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

typedef struct s_env_list
{
	char *env_var;
	struct s_env_list *next;
}	t_env_list;

//free 2d array
void free_2d(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
/***************************************************************************/
//check the length of 2d array
int ft_2d_len(char **str)
{
	int	i;

	i = -1;
	while (str[++i]);
	return (i);
}

t_env_list	*store_env(char **envp)
{
	t_env_list	*env_list;
	t_env_list	*new;
	int			i;

	env_list = NULL;
	i = -1;
	while (envp[++i])
	{
		new = malloc(sizeof(t_env_list));
		if (new == NULL)
		{
			printf("malloc failed\n");
			free_2d(envp);
			exit(EXIT_FAILURE);
		}
		new->env_var = ft_strdup(envp[i]);
		new->next = env_list;
		env_list = new;
	}
	return (env_list);
}

void print_env(t_env_list *env_list)
{
	t_env_list	*tmp;

	tmp = env_list;
	while (tmp)
	{
		ft_printf("%s\n", tmp->env_var);
		tmp = tmp->next;
	}
}

void clear_env_list(t_env_list *env_list)
{
	t_env_list	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp->env_var);
		free(tmp);
	}
}

char *get_env_value(t_env_list *env_list, char *name)
{
	t_env_list	*tmp;
	char		*value;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->env_var, name, ft_strlen(name)) == 0)
		{
			value = ft_strchr(tmp->env_var, '=') + 1;
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	check_var(char **cmd)
{
	int	i;

	i = 1;
	if (ft_isalpha(cmd[i][0]) == 0 || ft_strchr(cmd[i], '=') != NULL) //check for alpha or check for value in the env variable
	{
		printf("minishell: unset: `%s': not a valid identifier\n", cmd[i]);
		return (1);
	}
	return (0);
}

int	unset_var(t_env_list *env_list, char *cmd)
{
	t_env_list	*current;
	t_env_list	*prev;

	current = env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->env_var, cmd, ft_strlen(cmd)) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				env_list = current->next;
			free(current->env_var);
			free(current);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

int	unset_option(t_env_list *env_list, char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (check_var(cmd))
			return (1);
		else
			unset_var(env_list, cmd[i]);
		i++;
	}
	return (0);
}

int main(int ac, char **av, char **env)
{
	t_env_list	*env_list;
	env_list = store_env(env);
	print_env(env_list);
	printf("\n\n");
	if (ac > 1)
	{
		unset_option(env_list, av);
		print_env(env_list);
	}
	clear_env_list(env_list);
	return 0;
}