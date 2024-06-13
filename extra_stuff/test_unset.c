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
/****************************************EXPORT PART**********************************************************/

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

/*****************************************UNSET PART*******************************************************/


void remove_env_var(t_env_list *env_list, char *cmd)
{
	t_env_list	*current;
	t_env_list	*prev;
	char *name;

	current = env_list;
	prev = NULL;
	while(current)
	{
		name = get_name(current->env_var);
		if (ft_strncmp(cmd, name, ft_strlen(name)) == 0)
		{
			printf("\nname: not found: %i\n", ft_strncmp(cmd, name, ft_strlen(name)));
			// break;
			prev = current;
			current = current->next;
		}
		else
		 {
		    printf("\nname: found: %i\n", ft_strncmp(cmd, name, ft_strlen(name)));
			// break;
			free(current->env_var);
			free(current);
			if (prev != NULL)
				prev = current->next;
			else
				env_list = current->next;
		}
	}
	current = env_list;
}

int	unset_option(t_env_list *env_list, char **cmd)
{
	int	i;

	i = 1;
	if (cmd[i] != NULL)
	{
		if (check_name_exist(env_list,cmd[i]) == TRUE)
		{
			printf("\ncheck name exist: yes\n");
			remove_env_var(env_list, cmd[i]);
			return (0);
		}
	}
	return (1);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	t_env_list	*env_list;
	env_list = store_env(env);
	print_env(env_list);
	printf("\n\n");
	printf("--------------------------unset--------------------------\n");
	unset_option(env_list, av);
	print_env(env_list);
	clear_env_list(env_list);
	return 0;
}