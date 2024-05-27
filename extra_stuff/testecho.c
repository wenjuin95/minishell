#include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

//check whether had "-n" in echo command
static int	check_for_n(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] != '-')
			return (FALSE);
		i++;
		if (arg[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	echo_option(char **arg)
{
	int	i;
	int	n_flag;
	
	i = 1;
	n_flag = FALSE;
	while (arg[i] != NULL && check_for_n(arg[i]) == TRUE)
	{
		n_flag = TRUE;
		i++;
	}
	while (arg[i] != NULL)
	{
		printf("%s", arg[i]);
		if (arg[i + 1] != NULL) //if not last argument
			printf(" "); //print space and continue
		i++;
	}
	if (n_flag == FALSE) 
		printf("\n");
	return (0);
}

int main(int ac, char **av)
{
	(void)ac;
	echo_option(av);
	return (0);
}