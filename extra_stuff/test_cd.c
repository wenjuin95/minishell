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
		// ft_printf("name: %s\n", tmp->env_name); //debug
		// ft_printf("value: %s\n\n", tmp->env_value); //debug
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

/************************************EXPORT PART******************************************************************/

//function search the variable in the env list and get the value
char *search_env_value(t_env_list *env_list, char *name)
{
    t_env_list *current = env_list;

    while (current != NULL)
    {
        if (ft_strncmp(current->env_name, name, ft_strlen(current->env_name)) == 0)
        {
            return (ft_strdup(current->env_value));
        }
        current = current->next;
    }
    return NULL; // Return NULL if the environment variable is not found
}

//function check env variable had value
int	check_env_value(char *env_var)
{
	if (ft_strchr(env_var, '=') != NULL)
		return (TRUE);
	return (FALSE);
}

//function check the name exist in env list
int	check_exist_name(t_env_list *env_list, char *env_var)
{
	t_env_list	*current;

	current = env_list;
	while (current)
	{
		if (ft_strncmp(current->env_name, env_var,
				ft_strlen(current->env_name)) == 0)
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}


void replace_env_var(t_env_list *env_list, char *new_env_var)
{
	t_env_list	*current;
	char		*temp;

	current = env_list;
	while (current)
	{
		if (ft_strncmp(current->env_name, new_env_var, ft_strlen(current->env_name)) == 0)
		{
			temp = current->env_var;
			current->env_var = new_env_var;
			current->env_name = get_env_name(new_env_var);
			current->env_value = get_env_value(new_env_var, current->env_name);
			free(temp);
			return ;
		}
		current = current->next;
	}
}

void add_env_var(t_env_list *env_list, char *new_env_var)
{
	t_env_list	*new;
	t_env_list	*current;

	new = malloc(sizeof(t_env_list));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->env_var = new_env_var;
	new->env_name = get_env_name(new_env_var);
	new->env_value = get_env_value(new->env_var, new->env_name);
	new->next = NULL;
	current = env_list;
	while (current->next)
		current = current->next;
	current->next = new;
}

//function to store the environment variables to export
int update_env_var(t_env_list *env_list, char *name, char *value)
{
	t_env_list	*current;
	char		*new_env_var;
	char		*new_env_value;

	current = env_list;
	if (value == NULL)
		value = "''"; //if no value, assign single quote
	new_env_value = ft_strjoin("=", value);
	// printf("value: %s\n", new_env_value); //debug
	new_env_var = ft_strjoin(name, new_env_value);
	free(new_env_value);
	// printf("new env: %s\n", new_env_var); //debug
	if (new_env_var == NULL)
		return (FALSE);
	if (check_exist_name(current, name) == TRUE)
	{
		replace_env_var(env_list, new_env_var);
		return (TRUE);
	}
	else
	{
		add_env_var(env_list, new_env_var);
		return (TRUE);
	}
	return (TRUE);
}

/************************************CD PART******************************************************************/

//function to get the home directory
int	get_home_dir(t_env_list *env_list)
{
	char *home;
	t_env_list *current;

	current = env_list;
	replace_env_var(current, ft_strjoin("OLDPWD=", search_env_value(current, "PWD"))); //replace old pwd with current pwd
	home = search_env_value(current, "HOME"); //get the home directory value
	if (home == NULL)
	{
		ft_printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(home) == 0) //change to home directory
	{
		replace_env_var(current, ft_strjoin("PWD=", home)); //replace pwd with home directory
		return (0);
	}
	return (1);
}

//function changing the current working directory with specified arguments.
int	cd_option(t_env_list *env_list, char **cmd)
{
	char		*current_dir;
	t_env_list	*current;
	int			i;

	current = env_list;
	i = 1;
	if (cmd[i] == NULL) //if no argument is given, change to home directory
		return (get_home_dir(current));
	if (chdir(cmd[i]) == -1) //if the directory does not exist
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", cmd[i]);
		return (1);
	}
	else
	{
		replace_env_var(current, ft_strjoin("OLDPWD=", search_env_value(current, "PWD"))); //replace old pwd with current pwd
		current_dir = getcwd(NULL, 0); //get current working directory value
		if (current_dir == NULL)
			return (1);
		update_env_var(current, "PWD", current_dir); //replace pwd with current working directory
		free(current_dir);
		return (0);
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_env_list	*env_list;
	env_list = store_env(env);
	print_env(env_list);
	printf("\n\n");
	// printf("-----------------------original------------------------------\n");
	// char *ori = search_env_value(env_list, "OLDPWD"); //debug
	// printf("OLDPWD value: %s\n", ori);
	// free(ori);

	// char *ori2 = search_env_value(env_list, "PWD"); //debug
	// printf("PWD value: %s\n", ori2);
	// free(ori2);

	printf("-----------------------after cd------------------------------\n");
	int i = cd_option(env_list, av);
	//print_env(env_list);
	
	// char *value = search_env_value(env_list, "OLDPWD"); //debug
	// printf("OLDPWD value: %s\n", value);
	// free(value);

	// char *value2 = search_env_value(env_list, "PWD"); //debug
	// printf("PWD value: %s\n", value2);
	// free(value2);
	clear_env_list(env_list);
}