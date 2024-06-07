#include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

typedef struct s_env_list
{
	char				*env_name;
	char				*env_value;
	char				*env_var;
	struct s_env_list	*next;
}	t_env_list;


/****************************************ENV PART************************************************************/

//function for get the value of the env variable
char *get_env_value(char *env_var, char *name)
{
	int		i;
	char	*value;

	if (ft_strncmp(env_var, name, ft_strlen(env_var)) == 0) //handle if no value 
		return (value = ft_strdup(""));
	i = ft_strlen(name) + 1; //get the length of the name with "="
	value = ft_strdup(env_var + i); //get the value of the env variable
	if (value == NULL)
		return (NULL);
	return (value);
}


//function get env name
char	*get_env_name(char *env_var)
{
	char *name;
	int i;

	i = 0;
	while (env_var[i] != '=')
		i++;
	name = ft_substr(env_var, 0, i);
	return (name);
}

//function make env to link list
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
			return (NULL);
		new->env_var = ft_strdup(envp[i]);
		new->env_name = get_env_name(envp[i]);
		new->env_value = get_env_value(new->env_var, new->env_name);
		new->next = env_list;
		env_list = new;
	}
	return (env_list);
}

//function to print environment variable
void print_env(t_env_list *env_list)
{
	t_env_list	*tmp;

	tmp = env_list;
	while (tmp)
	{
		ft_printf("%s\n", tmp->env_var);
		ft_printf("name: %s\n", tmp->env_name); //debug
		ft_printf("value: %s\n\n", tmp->env_value); //debug
		tmp = tmp->next;
	}
}

//function to clear env list
void clear_env_list(t_env_list *env_list)
{
	t_env_list	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp->env_var);
		free(tmp->env_name);
		free(tmp->env_value);
		free(tmp);
	}
}

/*****************************************UNSET PART*******************************************************/

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

void	unset_var(t_env_list *env_list, char *cmd)
{
	t_env_list	*current;
	t_env_list	*prev;

	current = env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(cmd, current->env_name, ft_strlen(current->env_name)) == 0) //compare the name of the env variable
		{
			if (prev)
				prev->next = current->next;
			else
				env_list = current->next;
			free(current->env_var);
			free(current->env_name);
			free(current->env_value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
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
	int i;
	t_env_list	*env_list;
	env_list = store_env(env);
	print_env(env_list);
	printf("\n\n");
	printf("--------------------------unset--------------------------\n");
	if (ac > 1)
	{
		unset_option(env_list, av);
		print_env(env_list);
		// /*******debug***********/
		// i = unset_option(env_list, av);
		// if (i == 1)
		// 	printf("nothing to remove\n");
		// else
		// 	printf("remove success\n");
	}
	else
		clear_env_list(env_list);
	return 0;
}