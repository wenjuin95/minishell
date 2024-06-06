#include "../libft/libft.h"

#define TRUE 1
#define FALSE 0

typedef struct s_env_list
{
	char				*env_name;
	char				*env_value;
	char				*env_var;
	struct s_env_list	*next;
}	t_env_list;

/****************************************ENV PART************************************************************/

//function do link list
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
			exit(EXIT_FAILURE);
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

/***********************************EXPORT PART**************************************************/

void sort_env(t_env_list *env_list)
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
		printf("declare -x %s\n", current->env_var);
		current = current->next;
	}
}

//REPLACE :: check env variable had value
int check_env_value(char *env_var)
{
	if (ft_strchr(env_var, '=') != NULL)
		return (TRUE);
	return (FALSE);
}

//REPLACE :: check the name exist in env list
int check_exist_name(t_env_list *env_list, char *env_var)
{
	t_env_list	*current;

	current = env_list;
	while (current)
	{
		if (ft_strncmp(current->env_name, env_var, ft_strlen(current->env_name)) == 0)
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

/*
*	1. check name exist in env list
*	2. if exist, replace the value, if not add the new env variable
*/
//function to store the environment variables to export
int add_replace_env_var(t_env_list *env_list, char *env_name, char *env_value)
{
	t_env_list	*current;
	char		*new_env_var;
	char		*new_env_value;

	current = env_list;
	if (env_value == NULL)
		env_value = "''"; //if no value, assign single quote
	new_env_value = ft_strjoin("=", env_value);
	printf("value: %s\n", new_env_value); //debug
	new_env_var = ft_strjoin(env_name, new_env_value);
	free(new_env_value);
	printf("new env: %s\n", new_env_var); //debug
	if (new_env_var == NULL)
		return (FALSE);
	if (check_exist_name(current, env_name) == TRUE)
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

// function for export command
int export_option(t_env_list *env_list, char **cmd)
{
	int		i;
	char	*name;
	char	*value;

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
		name = get_env_name(cmd[i]);
		value = get_env_value(cmd[i], name);
		add_replace_env_var(env_list, name, value);
		print_env(env_list); //not sure export or env
		free(name);
		free(value);
		return (0);
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_env_list	*env_list;
	env_list = store_env(env);
	// printf("--------------------------print env--------------------------\n");
	// print_env(env_list);
	// printf("\n\n");
	// printf("--------------------------print_export--------------------------\n");
	// print_export(env_list);
	// printf("\n\n");
	// // printf("--------------------------add or replace env--------------------------\n");
	// char *name = get_env_name(av[1]);
	// char *value = get_env_value(av[1], name);
	// printf("input name: %s\n", name); //debug
	// printf("input value: %s\n", value); //debug
	// int flag = add_replace_env_var(env_list, name, value);
	// if (flag == FALSE)
	// 	printf("FUNCTION FAILED\n\n"); //debug
	// else
	// 	printf("FUNCTION SUCCESS\n\n"); //debug
	// print_env(env_list);
	// printf("\n\n");
	printf("--------------------------export option--------------------------\n");
	export_option(env_list, av);
	//print_env(env_list);

	clear_env_list(env_list);
	// free(name);
	// free(value);
}