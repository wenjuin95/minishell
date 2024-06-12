#include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

// int exit_output(char **cmd, int section)
// {
// 	if (section == 1)
// 	{
// 		ft_printf("exit\nminishell: exit: too many arguments\n");
// 		return (1);
// 	}
// 	else if (section == 2)
// 	{
// 		ft_printf("exit\nminishell: exit: %s: numeric argument required\n",
// 			cmd[1]);
// 		return (2);
// 	}
// 	return (0);
// }

// int exit_option(char **cmd)
// {
// 	int	i;
// 	int	nb;

// 	if (*cmd != NULL && ft_strncmp(*cmd, "./a.out", 8) != 0)
// 		return (0);
// 	i = -1;
// 	if (cmd[1] != NULL)
// 	{
// 		while (cmd[1][++i])
// 			if (ft_isdigit(cmd[1][i]) == FALSE)
// 				return (exit_output(cmd, 2));
// 		nb = ft_atoi(cmd[1]);
// 		return (nb % 256);
// 		if (cmd[2] != NULL)
// 			return (exit_output(cmd, 1));
// 	}
// 	return (0);
// }

/*
*	exit
*	- you just exit and return 0
*	
*	exit 123
*	- you exit and return 123
*
*	exit 123 456
*	- you can't exit but print exit and print error
*
*	exit 123 das
*	- you can't exit but print exit and print error
*	
*	exit asda
*	- you exit and print exit and print error
*	return (255);
*
*  exit dada dadas
*	- you exit and print exit and print error
*	return (255)
*/

void	exit_option(char **cmd)
{
	int	i;

	i = 1;
	if (cmd[i] == NULL)
		exit(0);
	else if (cmd[i] != NULL)
	{
		if (ft_isdigit(cmd[i][0]) == FALSE)
		{
			ft_printf("exit\nminishell: exit: %s: numeric argument required\n",
				cmd[i]);
			exit(255);
		}
		else
		{
			if (cmd[i+1] != NULL)
			{
				ft_printf("exit\nminishell: exit: too many argument\n",
				cmd[i]);
			}
			else
				exit(ft_atoi(cmd[i]) % 256);
		}
	}
	else if (cmd[i] != NULL && cmd[i+1] != NULL)
	{
		// ft_printf("exit\nminishell: exit: too many arguments\n");
		if (ft_isdigit(cmd[i-1][0]) == TRUE)
		{
			printf("exit\nminishell: exit: too many arguments\n");
		}
		else
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n",
				cmd[i-1]);
			exit(255);
		}
	}
}


int main(int ac, char **av)
{
	(void)ac;
	exit_option(av);
	// exit (nb);
}