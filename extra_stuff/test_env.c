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

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_env_list	*env_list;
	env_list = store_env(env);
	env_option(env_list, av);
	clear_env_list(env_list);
}