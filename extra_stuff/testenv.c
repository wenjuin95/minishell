#include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

//free 2d array
void free_2d(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

//check the length of 2d array
int ft_2d_len(char **str)
{
	int	i;

	i = -1;
	while (str[++i]);
	return (i);
}

//function for storing environment variable
char	**store_env(char **envp)
{
	char	**env_storage;
	int		env_len;
	int		i;

	env_len = -1;
	while (envp[++env_len]); //get the length of envp
	// //test: the envp length
	//ft_printf("lenght of envp: %d\n\n", env_len);
	env_storage = (char **)malloc(sizeof(char *) * (env_len + 1));
	if (env_storage == NULL)
	{
		printf("malloc failed\n");
		free_2d(env_storage);
		exit(EXIT_FAILURE);
	}
	//copy the envp to env_storage
	i = -1;
	while (envp[++i])
	{
		env_storage[i] = ft_strdup(envp[i]);
		if (env_storage[i] == NULL)
		{
			free_2d(env_storage);
			return (NULL);
		}
	}
	env_storage[i] = NULL;
	return (env_storage);
}

//function to append environment variable
char **add_env(char **envp_storage, char *variable)
{
	char	**new_envp;
	int		i;

	if (variable == NULL)
		return (envp_storage);
	new_envp = malloc(sizeof(char *) * (ft_2d_len(envp_storage) + 2));
	if (new_envp == NULL)
		return (NULL);
	i = -1;
	while (envp_storage[++i])
		new_envp[i] = ft_strdup(envp_storage[i]);
	new_envp[i++] = ft_strdup(variable);
	new_envp[i] = NULL;
	free_2d(envp_storage);
	return (new_envp);
}

//function to print environment variable
void	print_environment(char **env_storage)
{
	int	i;

	i = -1;
	while (env_storage[++i])
		ft_printf("%s\n", env_storage[i]);
}

//funtion to get the value of the environment variable
char *get_env_value(char **env_storage, char *key)
{
	int		i;
	char	*value;

	i = -1;
	while (env_storage[++i])
	{
		if (ft_strncmp(env_storage[i], key, ft_strlen(key)) == 0)
		{
			value = ft_strchr(env_storage[i], '=') + 1;
			return (value);
		}
	}
	return (NULL);
}

char *get_env_variable(char **env_storage, char *name)
{
	int		i;

	i = -1;
	while (env_storage[++i])
	{
		if (ft_strncmp(env_storage[i], name, ft_strlen(name)) == 0)
			return (name);
	}
	return (NULL);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	//test store_env
	char **env_storage = store_env(env);
	print_environment(env_storage);
	printf("\n\n");
	
	//test add_env
	char **new= add_env(env_storage, "TEST=123");
	print_environment(new);
	printf("\n\n");

	//test get_env_value
	char *value = get_env_value(new, "TEST");
	printf("value: %s\n", value);

	//test get_env_name
	char *name = get_env_variable(new, "HELLO");
	printf("name: %s\n", name);

	return (0);
}