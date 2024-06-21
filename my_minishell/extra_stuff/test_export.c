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

/*
*	@brief	print the environment variable with "declare -x"
*	@param	env_list pointer to the link list
*/
// void print_export(t_env_list *env_list)
// {
// 	t_env_list	*current;

// 	current = env_list;
// 	while (current)
// 	{
// 		sort_env(current);
// 		ft_printf("declare -x %s\n", current->env_var);
// 		current = current->next;
// 	}
// }

void	store_export(t_env_list *env_list)
{
	t_env_list	*current;
	char		*declare_var;

	current = env_list;
	while (current)
	{
		declare_var = ft_strjoin("declare -x ", current->env_var);
		free(current->env_var);
		current->env_var = ft_strdup(declare_var);
		free(declare_var);
		current = current->next;
	}
}

/*
*	@brief	get the name of the environment variable
*	@param	env_var	environment variable
*	@return	name of the environment variable
*	@note need to free 
*/
char	*get_name(char *env_var)
{
	int		i;
	char	*name;
	
	if (env_var == NULL) //if env_var is empty, return empty string
	{
		name = ft_strdup("");
		return (name);
	}
	else if (ft_strchr(env_var, '=') == NULL) //if not value return name
	{
		name = ft_strdup(env_var);
		return (name);
	}
	else // if env_var have value then return name
	{
		i = -1;
		while (env_var[++i] != '=')
			;
		name = ft_substr(env_var, 0, i);
		return (name);
	}
}

/*
*	@brief	get the value of the environment variable
*	@param	env_var	environment variable
*	@return	value of the environment variable
*	@note need to free
*/
char	*get_value(char *env_var)
{
	int		i;
	char	*value;

	if (env_var == NULL) // if env_var is empty, return empty string
	{
		value = ft_strdup(""); 
		return (value);
	}
	else if (ft_strchr(env_var, '=') == NULL) //if not value return empty string
	{
		value = ft_strdup("");
		return (value);
	}
	else // if env_var have value then return value
	{
		i = -1;
		while (env_var[++i] != '=')
			;
		value = ft_substr(env_var, i + 1, ft_strlen(env_var) - i - 1);
		return (value);
	}
}
/*
*	@brief	check if the name of the environment variable exist
*	@param	env_list	pointer to the link list
*	@param	env_var		environment variable
*	@return	TRUE if exist, FALSE if not exist
*/
int	check_name_exist(t_env_list *env_list, char *env_var)
{
	char 	*name;
	
	name = get_name(env_var);
	while (env_list)
	{
		if (ft_strncmp(name, env_list->env_var, ft_strlen(name)) == 0)
		{
			free(name);
			return (TRUE);
		}
		env_list = env_list->next;
	}
	free(name);
	return (FALSE);
}

/*
*	@brief	join the name and value of the environment variable
*	@param	name	name of the environment variable
*	@param	value	value of the environment variable
*	@return	environment variable
*	@note need to free the return string
*/
char *ft_join_env(char *name, char *value)
{
	char *new_var;

	if (name == NULL) //if name is empty, return empty string
		name = ft_strdup("");
	if (value == NULL) //if value is empty, return empty string
		value = ft_strdup("");
	new_var = ft_strjoin(name, "="); //join name and =
	free(name);
	name = ft_strjoin(new_var, value); //join name= and value
	free(new_var);
	free(value);
	return (name); //return name=value
}

/*
*	@brief	replace the environment variable to the link list
*	@param	env_list	pointer to the link list
*	@param	new_var		environment variable
*/
void	replace_env_var(t_env_list *env_list, char *new_var)
{
	t_env_list	*current;
	char		*new_env_name;
	char		*env_name;

	current = env_list;
	while (current)
	{
		new_env_name = get_name(new_var);
		env_name = get_name(current->env_var);
		if (ft_strncmp(new_env_name, env_name, ft_strlen(new_env_name)) == 0)
		{
			free(current->env_var);
			current->env_var = ft_strdup(new_var);
			free(new_var);
			free(new_env_name);
			free(env_name);
			break ;
		}
		free(new_env_name);
		free(env_name);
		current = current->next;
	}
}

/*
*	@brief	add the environment variable to the link list
*	@param	env_list	pointer to the link list
*	@param	new_var		environment variable
*/
void	add_env_var(t_env_list *env_list, char *new_var)
{
	t_env_list	*current;

	current = env_list;
	while (current)
	{
		if (current->next == NULL)
		{
			current->next = malloc(sizeof(t_env_list));
			current->next->env_var = ft_strdup(new_var);
			free(new_var);
			current->next->next = NULL;
			break ;
		}
		current = current->next;
	}
}

/*
*	@brief	check if the environment variable exist or not and update it
*	@param	env_list	pointer to the link list
*	@param	env_var		environment variable
*/
// void	check_and_update_env(t_env_list *env_list, char *env_var)
// {
// 	char *name;
// 	char *value;
// 	char *new_var;

// 	if (check_name_exist(env_list, env_var) == TRUE)
// 	{
// 		if (env_var[ft_strlen(env_var) - 1] == '=')
// 		{
// 			name = get_name(env_var);
// 			value = get_value(env_var);
// 			new_var = ft_join_env(name, value);
// 			replace_env_var(env_list, new_var);
// 		}
// 		else
// 		{
// 			name = get_name(env_var);
// 			value = get_value(env_var);
// 			new_var = ft_join_env(name, value);
// 			replace_env_var(env_list, new_var);
// 			store_export(env_list);
// 		}
// 	}
// 	else
// 	{
// 		if (env_var[ft_strlen(env_var) - 1] == '=')
// 		{
// 			name = get_name(env_var);
// 			value = get_value(env_var);
// 			new_var = ft_join_env(name, value);
// 			add_env_var(env_list, new_var);
// 		}
// 		else
// 		{
// 			name = get_name(env_var);
// 			value = get_value(env_var);
// 			new_var = ft_join_env(name, value);
// 			add_env_var(env_list, new_var);
// 			store_export(env_list);
// 		}
// 	}
// }
void	check_and_update_env(t_env_list *env_list, char *env_var)
{
	char *name;
	char *value;
	char *new_var;

	if (check_name_exist(env_list, env_var) == TRUE)
	{
		name = get_name(env_var);
		value = get_value(env_var);
		new_var = ft_join_env(name, value);
		replace_env_var(env_list, new_var);
		if (env_var[ft_strlen(env_var) - 1] != '=')
			store_export(env_list);
	}
	else
	{
		name = get_name(env_var);
		value = get_value(env_var);
		new_var = ft_join_env(name, value);
		if (env_var[ft_strlen(env_var) - 1] != '=')
			store_export(env_list);
		add_env_var(env_list, new_var);
	}
}

/*
*	@brief	handle export command
*	@param	env_list	pointer to the link list
*	@param	cmd			argument
*	@return	0 if success, 1 if error
*/
int export_option(t_env_list *env_list, char **cmd)
{
	int		i;

	i = 1;
	if (cmd[i] == NULL)
	{
		store_export(env_list);
		sort_env(env_list);
		print_env(env_list);
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
	// printf("--------------------------export option--------------------------\n");
	// export_option(env_list, av);
	//print_env(env_list);
	// printf("---------------------check name and value--------------------------\n");
	// char *name = get_name(av[1]);
	// printf("name: [%s]\n", name);
	// char *value = get_value(av[1]);
	// printf("value: [%s]\n", value);
	// free(name);
	// free(value);
	// printf("\n\n");
	// printf("---------------------check name exist--------------------------\n");
	// if (check_name_exist(env_list, av[1]) == TRUE)
	// 	printf("name exist\n");
	// else
	// 	printf("name not exist\n");
	// printf("\n\n");
	// printf("---------------------join name and value--------------------------\n");
	// char *new_var = ft_join_env(name, value);
	// printf("new_var: [%s]\n", new_var);
	// //free(new_var);
	// printf("\n\n");
	// printf("--------------------replace the exist var--------------------------\n");
	// replace_env_var(env_list, new_var);
	// print_env(env_list);
	// printf("--------------------add the var that not exist--------------------------\n");
	// add_env_var(env_list, new_var);
	// print_env(env_list);
	printf("---------------------export option--------------------------\n");
	if (export_option(env_list, av) == 0)
		print_env(env_list);
	
	clear_env_list(env_list);
	// free(name);
	// free(value);
}