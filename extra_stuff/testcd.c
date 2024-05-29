#include "../libft/libft.h"

/*********************************************************************************************************************/
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

void	print_environment(char **env_storage)
{
	int	i;

	i = -1;
	while (env_storage[++i])
		ft_printf("%s\n", env_storage[i]);
}

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

char **add_env(char **env_storage, int len)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(len + 1, sizeof(char *));
	if (new_env == NULL)
		return (NULL);
	i = 0;
	while (env_storage[i])
	{
		new_env[i] = ft_strdup(env_storage[i]);
		free(env_storage[i]);
		i++;
	}
	free(env_storage);
	return (new_env);
}

int	env_index(char **env_storage, char *name)
{
	int		i;
	char	*env_name;

	env_name = ft_strjoin(name, "=");
	if (env_name == NULL)
		return (-1);
	i = -1;
	while (env_storage[++i])
	{
		if (ft_strncmp(env_storage[i], env_name, ft_strlen(env_name)) == 0)
		{
			free(env_name);
			return (i);
		}
	}
	free(env_name);
	return (-1);
}

char **add_or_replace_env(char **env_storage, char *name, char *value)
{
    int		index;
    char	*env_value;

    index = env_index(env_storage, name);
    if (value == NULL)
        value = "";
    env_value = ft_strjoin("=", value); //join value with "="
    if (env_value == NULL)
        return (env_storage);
    if (index != -1 && env_storage[index] != NULL)
    {
        //replace existing env variable
        free(env_storage[index]);
        env_storage[index] = ft_strjoin(name, env_value); // join name with value
    }
    else
    {
        //add new env variable
        index = ft_2d_len(env_storage);
        env_storage = add_env(env_storage, index+1); //add new env variable
        if (env_storage == NULL)
            return (NULL);
        env_storage[index] = ft_strjoin(name, env_value); //join name with value
    }
    free(env_value);
    return (env_storage);
}
/*********************************************************************************************************************/

int	get_home(char **env_storage)
{
	char *home;

	env_storage = add_or_replace_env(env_storage, "OLDPWD", 
		get_env_value(env_storage, "PWD"));
	home = get_env_value(env_storage, "HOME");
	if (home == NULL)
	{
		ft_printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(home) == 0)
	{
		env_storage = add_or_replace_env(env_storage, "PWD", home);
		return (0);
	}
	return (1);
}

//function changing the current working directory with specified arguments.
int cd_option(char **env_storage, char **cmd)
{
	char *current;

	if (cmd[1] == NULL)
		return (get_home(env_storage));
	if (chdir(cmd[1]) == -1)
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", cmd[1]);
		return (1);
	}
	env_storage = add_or_replace_env(env_storage, "OLDPWD", 
		get_env_value(env_storage, "PWD"));
	current = getcwd(NULL, 0);
	if (current == NULL)
		return (1);
	env_storage = add_or_replace_env(env_storage, "PWD", current);
	free(current);
	return (0);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	char **storage = store_env(env);
	print_environment(storage);
	printf("\n");
	if (cd_option(storage, av) != 1)
		print_environment(storage);
}