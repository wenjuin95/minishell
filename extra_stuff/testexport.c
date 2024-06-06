#include "../libft/libft.h"
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct s_env_list
{
	char				*env_name;
	char				*env_value;
	char				*env_var;
	struct s_env_list	*next;
}	t_env_list;

/****************************************************************************************************/

void free_2d(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int ft_2d_len(char **str)
{
	int	i;

	i = -1;
	while (str[++i]);
	return (i);
}

// /****************************************************************************************************/

// //function to store environment variable to env_storage
// char	**store_env(char **envp)
// {
// 	char	**env_storage;
// 	int		env_len;
// 	int		i;

// 	env_len = -1;
// 	while (envp[++env_len]); //get the length of envp
// 	env_storage = (char **)malloc(sizeof(char *) * (env_len + 1));
// 	if (env_storage == NULL)
// 	{
// 		printf("malloc failed\n");
// 		free_2d(env_storage);
// 		exit(EXIT_FAILURE);
// 	}
// 	i = -1;	//copy the envp to env_storage
// 	while (envp[++i])
// 	{
// 		env_storage[i] = ft_strdup(envp[i]);
// 		if (env_storage[i] == NULL)
// 		{
// 			free_2d(env_storage);
// 			return (NULL);
// 		}
// 	}
// 	env_storage[i] = NULL;
// 	return (env_storage);
// }

// //function to print environment variable
// void	print_environment(char **env_storage)
// {
// 	int	i;

// 	i = -1;
// 	while (env_storage[++i])
// 		ft_printf("%s\n", env_storage[i]);
// }

// //function to get the environment variable value
// char *get_env_value(char **env_storage, char *value)
// {
// 	int		i;

// 	i = -1;
// 	while (env_storage[++i])
// 	{
// 		if (ft_strncmp(env_storage[i], value, ft_strlen(value)) == 0)
// 		{
// 			value = ft_strchr(env_storage[i], '=') + 1;
// 			return (value);
// 		}
// 	}
// 	return (NULL);
// }

// /****************************************************************************************************/
// //function to memory allocate for new environment variable
// char	**malloc_env(char **env_storage, int len)
// {
// 	char	**new_env;
// 	int		i;
// 	new_env = ft_calloc(len + 1, sizeof(char *));
// 	if (new_env == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (env_storage[i])
// 	{
// 		new_env[i] = ft_strdup(env_storage[i]);
// 		if (new_env[i] == NULL)
// 		{
// 			free_2d(new_env);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	return (new_env);
// }

// //function to get the index of the environment variable
// /*
// *	success: return the index of the environment variable
// *	failure: return -1
// */
// int	env_position(char **env_storage, char *env_var)
// {
// 	int		i;

// 	if (env_var == NULL)
// 		return (-1);
// 	i = -1;
// 	while (env_storage[++i])
// 	{
// 		if (ft_strncmp(env_storage[i], env_var, ft_strlen(env_var)) == 0)
// 			return (i);
// 	}
// 	return (-1);
// }

// //TODO ::need redo
// //function to add or replace environment variable
// /*
// *	success: return TRUE
// *	failure: return FALSE
// */
// char **add_or_replace_env(char **env_storage, char *name, char *value)
// {
// 	int		pos;
// 	char	*new_value;

// 	pos = env_position(env_storage, name); //get the position
// 	if (value == NULL || *value == '\0')
// 		new_value = ""; //if no value, assign empty string
// 	else
// 		new_value = ft_strjoin("=", value); //if got value assign the value with "="
// 	if (pos == -1) //if position not found
// 	{
// 		char **new_env = malloc_env(env_storage, ft_2d_len(env_storage) + 1);
// 		if (new_env == NULL)
// 			return (NULL);
// 		new_env[ft_2d_len(env_storage)] = ft_strjoin(name, new_value);
// 		free_2d(env_storage);
// 		return (new_env);
// 	}
// 	else
// 	{
// 		free(env_storage[pos]); //if found, free the memory
// 		env_storage[pos] = ft_strjoin(name, new_value); //assign the new value
// 		return (env_storage);
// 	}
// }

// //function found the env varible and remove it
// /*
// *	success: return TRUE
// *	failure: return FALSE
// */
// int	remove_env(char **env_storage, char *name)
// {
// 	int		i;
// 	int		index;

// 	index = env_position(env_storage, name); //get the position
// 	if (index == -1) // if not found
// 		return (FALSE);
// 	free(env_storage[index]); //if found, free the memory
// 	i = index; //if found, get the position and assign to i
// 	while (env_storage[i+1]) //skip the removed env variable position and store the rest of the env variable
// 	{
// 		env_storage[i] = env_storage[i+1];
// 		i++;
// 	}
// 	env_storage[i] = NULL;
// 	return (TRUE);
// }

// /****************************************************************************************************/

// void	sort_env(char **env_storage)
// {
// 	int		i;
// 	int		j;
// 	int		len;
// 	char	*temp;

// 	i = 0;
// 	len = ft_2d_len(env_storage);
// 	while (i < len)
// 	{
// 		j = i + 1;
// 		while (j < len)
// 		{
// 			if (ft_strncmp(env_storage[i], env_storage[j],
// 					ft_strlen(env_storage[i])) > 0)
// 			{
// 				temp = env_storage[i];
// 				env_storage[i] = env_storage[j];
// 				env_storage[j] = temp;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// //function store the environment variables to export
// char	**store_to_export(char **env_storage)
// {
// 	int	i;

// 	sort_env(env_storage);
// 	i = 0;
// 	while (env_storage[i])
// 	{
// 		env_storage[i] = ft_strjoin("declare -x ", env_storage[i]);
// 		i++;
// 	}
// 	return (env_storage);
// }

// //function either store at env_storage or export storage
// char	**store_option(char **env_storage, char **cmd)
// {
// 	int		i;
// 	char	**tmp_env;

// 	i = 1;
// 	while (cmd[i] != NULL)
// 	{
// 		if (ft_strchr(cmd[i], '=') != NULL) //if the variable had value
// 		{
// 			tmp_env = ft_split(cmd[i], '=');
// 			env_storage = add_or_replace_env(env_storage, tmp_env[0],
// 					tmp_env[1]);
// 			free_2d(tmp_env);
// 		}
// 		else //if the variable no value
// 		{
// 			env_storage = add_or_replace_env(env_storage, cmd[i], "");
// 			env_storage = store_to_export(env_storage);
// 		}
// 		i++;
// 	}
// 	return (env_storage);
// }

// //function for export command
// char **export_option(char **env_storage, char **cmd)
// {
// 	int		i;

// 	i = 1;
// 	if (cmd[i] == NULL) //env list + [declare -x] to export list
// 		return (store_to_export(env_storage));
// 	else //add the new env to the export list
// 	{
// 		if (ft_isalpha(cmd[i][0]) == 0)
// 		{
// 			printf("export: `%s': not a valid identifier\n", cmd[i]);
// 			return (env_storage);
// 		}
// 		env_storage = store_option(env_storage, cmd);
// 		return (env_storage);
// 	}
// }

// /****************************************************************************************************/

// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	// char **env_storage = store_env(env);
// 	// print_environment(env_storage);
// 	// printf("\n\n");
// 	// printf("--------------------------check malloc_env---------------------\n\n");
// 	// char **new_env = malloc_env(env, ft_2d_len(env) + 1);
// 	// if (new_env == NULL)
// 	// {
// 	// 	printf("malloc_env failed\n");
// 	// 	free_2d(new_env);
// 	// 	exit(EXIT_FAILURE);
// 	// }
// 	// else
// 	// {
// 	// 	printf("malloc_env success\n");
// 	// 	free_2d(new_env);
// 	// }
// 	// printf("\n\n");
// 	// printf("--------------------------check env_position---------------------\n\n");
// 	// int index = env_position(env, "PATH");
// 	// if (index == -1)
// 	// 	printf("env_position failed\n");
// 	// else
// 	// {
// 	// 	printf("env_position success\n");
// 	// 	printf("path index = %d\n", index);
// 	// }
// 	// printf("\n\n");
// 	// printf("--------------------------check add_or_replace_env---------------------\n\n");
// 	// char **env_storage = store_env(env);
// 	// char **new_env2 = add_or_replace_env(env_storage, "HOME", "");
// 	// print_environment(new_env2);
// 	// free_2d(new_env2);
// 	// printf("\n\n");
// 	// printf("--------------------------check env sort---------------------\n\n");
// 	// char **env_storage = store_env(env);
// 	// sort_env(env_storage);
// 	// print_environment(env_storage);
// 	// printf("\n\n");
// 	// printf("--------------------------check store_to_export---------------------\n\n");
// 	// char **env_storage = store_env(env);
// 	// print_environment(env_storage);
// 	// printf("\n\n");
// 	// char **new_env = store_to_export(env_storage);
// 	// print_environment(new_env);
// 	// printf("\n\n");
// 	printf("--------------------------check store_option---------------------\n\n");
// 	char **env_storage = store_env(env);
// 	char **new_env = export_option(env_storage, av);
// 	print_environment(new_env);
// 	free_2d(env_storage);
// 	free_2d(new_env);

// 	return (0);
// }

//function do link list
//function for get the value of the env variable
char *get_env_value(char *env_var, char *name)
{
	int		i;
	char	*value;

	i = ft_strlen(name) + 1;
	value = ft_strdup(env_var + i);
	if (value == NULL)
		exit(EXIT_FAILURE);
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
		ft_printf("%s\n", tmp->env_name); //debug
		ft_printf("%s\n", tmp->env_value); //debug
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

/******************************************************************************/

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
		if (current->env_name != NULL)
		{
			if(ft_strncmp(current->env_name, env_var, ft_strlen(current->env_name)) == 0)
			return (TRUE);
		}
		current = current->next;
	}
	return (FALSE);
}

/*
*	1. check name exist in env list
*	2. if exist, replace the value, if not add the new env variable
*/
//function to store the environment variables to export
int add_replace_env_var(t_env_list *env_list, char *env_name, char *env_value)
{
	// t_env_list	*new;
	t_env_list	*current;
	char		*new_env_var;
	char		*new_env_value;

	current = env_list;
	if (env_value == NULL)
		env_value = NULL;
	new_env_value = ft_strjoin("=", env_value);
	printf("new value: %s\n", new_env_value); //debug
	new_env_var = ft_strjoin(env_name, new_env_value);
	printf("new var: %s\n", new_env_var); //debug
	if (new_env_var == NULL)
		return (FALSE);
	if (check_exist_name(current, env_name) == TRUE)
	{
		printf("found\n"); //debug
		return (TRUE);
	}
	else
	{
		printf("not found\n"); //debug
		return (TRUE);
	}
	return (TRUE);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_env_list	*env_list;
	env_list = store_env(env);
	printf("--------------------------print env--------------------------\n");
	print_env(env_list);
	printf("\n\n");
	// printf("--------------------------print_export--------------------------\n");
	// print_export(env_list);
	// printf("\n\n");
	printf("--------------------------add or replace env--------------------------\n");
	int flag = add_replace_env_var(env_list, "SHELL", "hello");
	printf("flag: %d\n", flag); //debug
	print_env(env_list);

	// clear_env_list(env_list);
}