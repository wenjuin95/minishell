#include "../libft/libft.h"

# define TRUE 1
# define FALSE 0


typedef struct s_env_list
{
	char *env_var;
	struct s_env_list *next;
}	t_env_list;
/***************************************************************************/
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
/***************************************************************************/
// //function for storing environment variable
// char	**store_env(char **envp)
// {
// 	char	**env_storage;
// 	int		env_len;
// 	int		i;

// 	env_len = -1;
// 	while (envp[++env_len]); //get the length of envp
// 	// //test: the envp length
// 	//ft_printf("lenght of envp: %d\n\n", env_len);
// 	env_storage = (char **)malloc(sizeof(char *) * (env_len + 1));
// 	if (env_storage == NULL)
// 	{
// 		printf("malloc failed\n");
// 		free_2d(env_storage);
// 		exit(EXIT_FAILURE);
// 	}
// 	//copy the envp to env_storage
// 	i = -1;
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
// /***************************************************************************/
// //function to print environment variable
// void	print_environment(char **env_storage)
// {
// 	int	i;

// 	i = -1;
// 	while (env_storage[++i])
// 		ft_printf("%s\n", env_storage[i]);
// }
// /***************************************************************************/
// //funtion to get the value of the environment variable
// char *get_env_value(char **env_storage, char *key)
// {
// 	int		i;
// 	char	*value;

// 	i = -1;
// 	while (env_storage[++i])
// 	{
// 		if (ft_strncmp(env_storage[i], key, ft_strlen(key)) == 0)
// 		{
// 			value = ft_strchr(env_storage[i], '=') + 1;
// 			return (value);
// 		}
// 	}
// 	return (NULL);
// }
// /***************************************************************************/
// //function to add environment variable to the env_storage
// char	**add_env(char **env_storage, int len)
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
// /***************************************************************************/
// //function to get the index of the environment variable
// /*
// *	success: return the index of the environment variable
// *	failure: return -1
// */
// int	env_index(char **env_storage, char *name)
// {
// 	int		i;
// 	char	*env_name;

// 	env_name = ft_strjoin(name, "=");
// 	if (env_name == NULL)
// 		return (-1);
// 	i = -1;
// 	while (env_storage[++i])
// 	{
// 		if (ft_strncmp(env_storage[i], env_name, ft_strlen(env_name)) == 0)
// 		{
// 			free(env_name);
// 			return (i);
// 		}
// 	}
// 	free(env_name);
// 	return (-1);
// }
// /***************************************************************************/
// //function to add or replace environment variable
// /*
// *	success: return TRUE
// *	failure: return FALSE
// */
// char **add_or_replace_env(char **env_storage, char *name, char *value)
// {
//     int		index;
//     char	*env_value;

//     index = env_index(env_storage, name);
//     if (value == NULL)
//         value = "";
//     env_value = ft_strjoin("=", value); //join value with "="
//     if (env_value == NULL)
//         return (env_storage);
//     if (index != -1 && env_storage[index] != NULL)
//     {
//         //replace existing env variable
//         free(env_storage[index]);
//         env_storage[index] = ft_strjoin(name, env_value); // join name with value
//     }
//     else
//     {
//         //add new env variable
//         index = ft_2d_len(env_storage);
//         env_storage = add_env(env_storage, index+1); //add new env variable
//         if (env_storage == NULL)
//             return (NULL);
//         env_storage[index] = ft_strjoin(name, env_value); //join name with value
//     }
//     free(env_value);
//     return (env_storage);
// }
// /***************************************************************************/
// //function to remove environment variable
// /*
// *	success: return TRUE
// *	failure: return FALSE
// */
// int	remove_env(char **env_storage, char *name)
// {
// 	int		i;
// 	int		len;
// 	int		index;

// 	index = env_index(env_storage, name);
// 	if (index == -1)
// 		return (FALSE);
// 	free(env_storage[index]);
// 	i = index;
// 	len = index;
// 	//skip the removed env variable to store the rest of the env variable
// 	while (env_storage[i+1])
// 	{
// 		env_storage[i] = ft_strdup(env_storage[i+1]);
// 		free(env_storage[i+1]);
// 		i++;
// 		len++;
// 	}
// 	env_storage[len] = NULL;
// 	return (TRUE);
// }
// /***************************************************************************/
// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;

// 	//test store_env
// 	printf("---------------------store_env---------------------\n");
// 	char **env_storage = store_env(env);
// 	print_environment(env_storage);
// 	printf("\n\n");

// 	// //test add_or_replace_env
// 	// printf("-----------------add_replace---------------------\n");
// 	// char **new_env = add_or_replace_env(env_storage, "HOME2", "123");
// 	// print_environment(new_env);
// 	// printf("\n\n");

// 	//text add_env
// 	printf("---------------------add_env---------------------\n");
// 	char **new_env = add_env(env_storage, ft_2d_len(env_storage) + 1);
// 	print_environment(new_env);
// 	printf("\n\n");

// 	//test remove env
// 	printf("---------------------remove_env---------------------\n");
// 	remove_env(new_env, "HOME");
// 	print_environment(new_env);
// 	printf("\n\n");

// 	//test get_env_value
// 	printf("---------------------get value---------------------\n");
// 	char *value = get_env_value(new_env, "PWD");
// 	printf("value: %s\n\n", value);
// 	printf("\n\n");

// 	//text env_index
// 	printf("---------------------env_index---------------------\n");
// 	int index = env_index(new_env, "PWD");
// 	printf("index: %d\n\n", index);

// 	free_2d(env_storage);
// 	free_2d(new_env);
// 	return (0);
// }

//function do link list
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

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_env_list	*env_list;
	env_list = store_env(env);
	printf("--------------------------print env--------------------------\n");
	print_env(env_list);
	printf("\n\n");
	char *value = get_env_value(env_list, "PWD");
	printf("--------------------------print value--------------------------\n");
	printf("value: %s\n", value);
	clear_env_list(env_list);
}