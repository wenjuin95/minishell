#include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

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

/****************************************************************************************************/

//function to store environment variable to env_storage
char	**store_env(char **envp)
{
	char	**env_storage;
	int		env_len;
	int		i;

	env_len = -1;
	while (envp[++env_len]); //get the length of envp
	env_storage = (char **)malloc(sizeof(char *) * (env_len + 1));
	if (env_storage == NULL)
	{
		printf("malloc failed\n");
		free_2d(env_storage);
		exit(EXIT_FAILURE);
	}
	i = -1;	//copy the envp to env_storage
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

//function to print environment variable
void	print_environment(char **env_storage)
{
	int	i;

	i = -1;
	while (env_storage[++i])
		ft_printf("%s\n", env_storage[i]);
}

/****************************************************************************************************/

int	env_position(char **env_storage, char *env_var)
{
	int		i;

	if (env_var == NULL)
		return (-1);
	i = -1;
	while (env_storage[++i])
	{
		if (ft_strncmp(env_storage[i], env_var, ft_strlen(env_var)) == 0)
			return (i);
	}
	return (-1);
}

int	remove_env(char **env_storage, char *name)
{
	int		i;
	int		index;

	index = env_position(env_storage, name); //get the position
	if (index == -1) // if not found
		return (FALSE);
	free(env_storage[index]); //if found, free the memory
	i = index; //if found, get the position and assign to i
	while (env_storage[i+1]) //skip the removed env variable position and store the rest of the env variable
	{
		env_storage[i] = env_storage[i+1];
		i++;
	}
	env_storage[i] = NULL;
	return (TRUE);
}

/****************************************************************************************************/

char **unset_option(char **env_storage, char **cmd)
{
	int	i;
	int	position;

	i = 1;
	while (cmd[i])
	{
		if (ft_isalpha(cmd[i][0]) == 0 || ft_strchr(cmd[i], '=') != NULL)
		{
			printf("minishell: unset: `%s': not a valid identifier\n", cmd[i]);
			return (env_storage);
		}
		else
		{
			position = env_position(env_storage, cmd[i]);
			if (position != -1)
			{
				remove_env(env_storage, cmd[i]);
			}
		}
		i++;
	}
	return (env_storage);
}

/****************************************************************************************************/

int main(int ac, char **av, char **env)
{
	(void)ac;
	printf("------------test unset_option------------\n");
	char **env_storage = store_env(env);
	print_environment(env_storage);
	printf("\n\n");
	char **update_env = unset_option(env_storage, av);
	print_environment(update_env);
	free_2d(update_env);
}