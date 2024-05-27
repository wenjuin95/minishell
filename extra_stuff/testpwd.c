#include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

void	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}

int main(int ac, char **av)
{
	(void)av;
	if (ac == 1)
		pwd();
}