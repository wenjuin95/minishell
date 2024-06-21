#include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

int	pwd_option(char **cmd)
{
	int		i;
	char	*pwd;

	i = 1;
	if (cmd[i] == NULL)
	{
		pwd = NULL;
		pwd = getcwd(pwd, 0);
		printf("%s\n", pwd);
		free(pwd);
		return (0);
	}
	else
	{
		printf("pwd: %s: No such file or directory\n", cmd[i]);
		return (1);
	}
}

int main(int ac, char **av)
{
	(void)ac;
	pwd_option(av);
}