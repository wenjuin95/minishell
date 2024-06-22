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

t_env_list	*store_env(char **envp);
void print_env(t_env_list *env_list);
void clear_env_list(t_env_list *env_list);

int	check_name_exist(t_env_list *env_list, char *env_var);
char	*get_name(char *env_var);
char	*get_value(char *env_var);
void	replace_env_var(t_env_list *env_list, char *new_var);
char	*ft_join_env(char *name, char *value);


/****************************************ENV PART************************************************************/

/*
*	@brief store the environment variable to link list
*	@param envp	:: environment variable
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
*	@param env_list	:: pointer to the link list
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
*	@param env_list	:: pointer to the link list
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

/************************************EXPORT PART******************************************************************/

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

/*
*	@brief	get the name of the environment variable
*	@param	env_var :: environment variable
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
*	@brief	get the value of the environment variable
*	@param	env_var	:: environment variable
*	@return	value of the environment variable
*	@note need to free
*/
char	*get_value(char *env_var)
{
	int		i;
	char	*value;

	if (env_var == NULL) // if env_var is empty, return empty string
	{
		value = ft_strdup(""); 
		return (value);
	}
	else if (ft_strchr(env_var, '=') == NULL) //if not value return empty string
	{
		value = ft_strdup("");
		return (value);
	}
	else // if env_var have value then return value
	{
		i = -1;
		while (env_var[++i] != '=')
			;
		value = ft_substr(env_var, i + 1, ft_strlen(env_var) - i - 1);
		return (value);
	}
}

/*
*	@brief	replace the environment variable to the link list
*	@param	env_list :: pointer to the link list
*	@param	new_var	:: environment variable
*/
void	replace_env_var(t_env_list *env_list, char *new_var)
{
	t_env_list	*current;
	char		*new_env_name;
	char		*env_name;

	current = env_list;
	while (current)
	{
		new_env_name = get_name(new_var);
		env_name = get_name(current->env_var);
		if (ft_strncmp(new_env_name, env_name, ft_strlen(new_env_name)) == 0)
		{
			free(current->env_var);
			current->env_var = ft_strdup(new_var);
			free(new_var);
			free(new_env_name);
			free(env_name);
			break ;
		}
		free(new_env_name);
		free(env_name);
		current = current->next;
	}
}

/*
*	@brief	join the name and value of the environment variable
*	@param	name :: name of the environment variable
*	@param	value :: value of the environment variable
*	@return	name=value
*/
char	*ft_join_env(char *name, char *value)
{
	char *new_var;

	if (name == NULL) //if name is empty, return empty string
		name = ft_strdup("");
	if (value == NULL) //if value is empty, return empty string
		value = ft_strdup("");
	new_var = ft_strjoin(name, "="); //join name and =
	free(name);
	name = ft_strjoin(new_var, value); //join name= and value
	free(new_var);
	free(value);
	return (name); //return name=value
}

/************************************CD PART******************************************************************/

/*
*	@brief	search the environment variable in the link list and return the value
*	@param	env_list :: pointer to the link list
*	@param	env_name :: name of the environment variable you looking for
*	@return	value of the environment variable you looking for
*	@note need to free
*/
char *search_env_value(t_env_list *env_list, char *env_name)
{
	t_env_list	*current;
	char		*value;
	
	current = env_list;
	while (current)
	{
		if (ft_strncmp(env_name, current->env_var, ft_strlen(env_name)) == 0)
		{
			value = get_value(current->env_var);
			return (value);
		}
		current = current->next;
	}
	return NULL;
}

/*
*	@brief	return error massage
*	@param	cmd :: command
*	@return	1 mean fail
*/
int	get_err(char *cmd)
{
	ft_printf("minishell: cd: %s: No such file or directory\n", cmd);
	return (1);
}

/*
*	@brief	change the directory to main directory
*	@param	env_list :: pointer to the link list
*	@param	home_value :: value of the HOME environment variable
*	@param	pwd_value :: value of the PWD environment variable
*	@return	0 if success, 1 if fail
*/
int	main_dir(t_env_list *env_list, char *home_value, char *pwd_value)
{
	replace_env_var(env_list, ft_strjoin("OLDPWD=", pwd_value));
	free(pwd_value);
	if (home_value == NULL)
	{
		ft_printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(home_value) == 0)
	{
		replace_env_var(env_list, ft_strjoin("PWD=", home_value));
		free(home_value);
		return (0);
	}
	return (1);
}

/*
*	@brief change the PWD environment variable
*	@param	env_list :: pointer to the link list
* 	@return	0 if success, 1 if fail
*/
int	chg_pwd(t_env_list *env_list)
{
	char	*pwd;
	
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	replace_env_var(env_list, ft_strjoin("PWD=", pwd));
	free(pwd);
	return (0);
}

/*
*	@brief	cd option
*	@param	env_list :: pointer to the link list
*	@param	cmd :: command
*	@return	0 if success, 1 if fail
*/
int	cd_option(t_env_list *env_list, char **cmd)
{
	t_env_list	*current;
	char		*pwd;
	char		*home;
	int			i;

	i = 1;
	home = search_env_value(env_list, "HOME");
	pwd = search_env_value(env_list, "PWD");
	current = env_list;
	if (cmd[i] == NULL)
		return (main_dir(current, home, pwd));
	if (chdir(cmd[i]) != 0)
		return (get_err(cmd[i]));
	replace_env_var(current, ft_strjoin("OLDPWD=", pwd));
	return (chg_pwd(current));
	free(pwd);
	free(home);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_env_list	*env_list;
	env_list = store_env(env);
	print_env(env_list);
	printf("\n\n");
	// printf("-----------------------search_env_value------------------------------\n");
	// char *pwd = search_env_value(env_list, av[1]);
	// printf("PWD: %s\n", pwd);
	// free(pwd);
	// printf("\n");
	printf("-----------------------------cd option------------------------------\n");
	printf("---before---\n");
	char *OLDPWD = search_env_value(env_list, "OLDPWD");
	char *PWD = search_env_value(env_list, "PWD");
	printf("OLDPWD: %s\n", OLDPWD);
	printf("PWD: %s\n", PWD);
	free(OLDPWD);
	free(PWD);

	cd_option(env_list, av);
	// print_env(env_list);
	printf("---after---\n");
	char *OLDPWD2 = search_env_value(env_list, "OLDPWD");
	char *PWD2 = search_env_value(env_list, "PWD");
	printf("OLDPWD: %s\n", OLDPWD2);
	printf("PWD: %s\n", PWD2);
	free(OLDPWD2);
	free(PWD2);

	clear_env_list(env_list);
}