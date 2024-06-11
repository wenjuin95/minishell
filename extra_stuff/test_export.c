#include "../libft/libft.h"

#define TRUE 1
#define FALSE 0

typedef struct s_env_list
{
	char				*env_var;
	struct s_env_list	*next;
}	t_env_list;

/****************************************ENV PART************************************************************/

/*
*	@brief store the environment variable to link list
*	@param envp	environment variable
*/
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
		new->next = env_list;
		env_list = new;
	}
	return (env_list);
}

/*
*	@brief print the env variable
*	@param env_list	pointer to the link list
*/
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

/*
*	@brief handle env command
*	@param env_list	pointer to the link list
*	@param cmd		argument
*	@return	0 if success, 1 if error
*/
int	env_option(t_env_list *env_list, char **cmd)
{
	int	i;

	i = 1;
	if (cmd[i] == NULL)
	{
		print_env(env_list);
		return (0);
	}
	else
	{
		ft_printf("env: %s: No such file or directory\n", cmd[i]);
		return (1);
	}
}

/*
*	@brief clear the link list
*	@param env_list	pointer to the link list
*/
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

/***********************************EXPORT PART**************************************************/

/*
*	@brief	sort the environment variable in alphabetical order
*	@param	env_list	pointer to the link list
*/
void	sort_env(t_env_list *env_list)
{
	t_env_list	*current;
	t_env_list	*next;
	char		*temp;

	current = env_list;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (ft_strncmp(current->env_var, next->env_var,
					ft_strlen(current->env_var)) > 0)
			{
				temp = current->env_var;
				current->env_var = next->env_var;
				next->env_var = temp;
			}
			next = next->next;
		}
		current = current->next;
	}
}

void print_export(t_env_list *env_list)
{
	t_env_list	*current;

	current = env_list;
	while (current)
	{
		sort_env(current);
		ft_printf("declare -x %s\n", current->env_var);
		current = current->next;
	}
}
/*
* 	function need to do:
*	1.get_name
*	2.get_value
*	3.check_name_exist
*	4.update_env
*   5.replace_env_var
*   6.add_env_var
*/
void	check_and_update_env(t_env_list *env_list, char *env_var)
{
	char *name;
	char *value;
	char *new_var;

	if (check_name_exist(env_var) == TRUE)
	{
		name = get_name(env_var);
		value = get_value(env_var);
		new_var = update_env(env_list, name, value);	
		replace_env_var(env_list, new_var);
	}
	else
	{
		name = get_name(env_var);
		value = get_value(env_var);
		new_var = update_env(env_list, name, value);
		add_env_var(env_list, new_var);
	}

}

// function for export command
int export_option(t_env_list *env_list, char **cmd)
{
	int		i;

	i = 1;
	if (cmd[i] == NULL)
	{
		print_export(env_list);
		return (0);
	}
	else
	{
		if (ft_isalpha(cmd[i][0]) == 0)
		{
			printf("export: `%s': not a valid identifier\n", cmd[i]);
			return (1);
		}
		else
		{
			check_and_update_env(env_list, cmd[i]);
			return (0);
		}
	
	}
	return (0);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_env_list	*env_list;
	env_list = store_env(env);
	printf("--------------------------export option--------------------------\n");
	export_option(env_list, av);
	//print_env(env_list);

	clear_env_list(env_list);
	// free(name);
	// free(value);
}