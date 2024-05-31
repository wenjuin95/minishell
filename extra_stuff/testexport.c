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
// this to get the index of the environment variable if it exists
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
	char	*new_env;

    index = env_index(env_storage, name);
    if (value == NULL || *value == '\0')
        env_value = ft_strdup("");
	else
    	env_value = ft_strjoin("=", value); //join value with "="
    if (env_value == NULL)
        return (env_storage);
    if (index != -1 && env_storage[index] != NULL)        //replace existing env variable
    {
        new_env = ft_strjoin(name, env_value); // join name with value
		free(env_storage[index]);
		env_storage[index] = new_env;
    }
    else         //add new env variable
    {
        index = ft_2d_len(env_storage);
        env_storage = add_env(env_storage, index+1); //add new env variable
		if (env_storage == NULL)
			return (NULL);
       	new_env = ft_strjoin(name, env_value); //join name with value
		env_storage[index] = new_env;
    }
    free(env_value);
    return (env_storage);
}
/*********************************************************************************************************************/

void	sort_env(char **env_storage)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	i = 0;
	len = ft_2d_len(env_storage);
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(env_storage[i], env_storage[j],
					ft_strlen(env_storage[i])) > 0)
			{
				temp = env_storage[i];
				env_storage[i] = env_storage[j];
				env_storage[j] = temp;
			}
			j++;
		}
		i++;
	}
}

//function store the environment variables to export
char	**store_to_export(char **env_storage)
{
	int	i;

	sort_env(env_storage);
	i = 0;
	while (env_storage[i])
	{
		env_storage[i] = ft_strjoin("declare -x ", env_storage[i]);
		i++;
	}
	return (env_storage);
}

char **store_option(char **env_storage, char **cmd)
{
	int		i;
	char	**tmp_env;

	i = 1;
	while (cmd[i] != NULL)
	{
		if (ft_strchr(cmd[i], '=') != NULL)
		{
			tmp_env = ft_split(cmd[i], '=');
			env_storage = add_or_replace_env(env_storage, tmp_env[0],
					tmp_env[1]);
			free_2d(tmp_env);
		}
		else
		{
			env_storage = add_or_replace_env(env_storage, cmd[i], "");
			env_storage = store_to_export(env_storage);
		}
		i++;
	}
	return (env_storage);
}

//function for export command
char **export_option(char **env_storage, char **cmd)
{
	int		i;

	i = 1;
	if (cmd[i] == NULL)
		return (store_to_export(env_storage));
	else
	{
		env_storage = store_option(env_storage, cmd);
		//print_environment(env_storage);
		return (env_storage);
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	char **new_env = store_env(env);
	print_environment(new_env);
	printf("\n\n");
	new_env = export_option(new_env, av);
	print_environment(new_env);
}