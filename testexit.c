// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>

#include "libft/libft.h"

# define TRUE 1
# define FALSE 0

// int check_digit(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (ft_isdigit(str[i]) != 0)
// 			return (FALSE);
// 		i++;
// 	}
// 	return (TRUE);
// }

// void	exit_check(char **cmd)
// {
// 	if (cmd[1] != NULL && cmd[2] != NULL)
// 	{
// 		if (check_digit(cmd[1]) == TRUE)
// 		{
// 			ft_printf("exit\nminishell: exit: %s: numeric argument required\n",
// 				cmd[1]);
// 			exit(1);
// 		}
// 		else
// 		{
// 			ft_printf("exit\nminishell: exit: too many arguments\n");
// 		}
// 	}
// 	else if (cmd[1] != NULL && check_digit(cmd[1]) == TRUE)
// 	{
// 		ft_printf("exit\nminishell: exit: %s: numeric argument required\n",
// 			cmd[1]);
// 		exit(1);
// 	}
// 	else
// 	{
// 		ft_printf("exit\n");
// 		exit(0);
// 	}
// }

// void	exit_cmd(char **cmd)
// {
// 	int	nb;
	
// 	if (cmd[1] != NULL)
// 	{
// 		exit_check(cmd);
// 		exit(ft_atoi(cmd[1]));
// 	}
// 	else
// 	{
// 		ft_printf("exit\n");
// 		exit(0);
// 	}
// }

int exit_output(char **cmd, int section)
{
	if (section == 1)
	{
		ft_printf("exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	else if (section == 2)
	{
		ft_printf("exit\nminishell: exit: %s: numeric argument required\n",
			cmd[1]);
		return (2);
	}
	return (0);
}

int exit_arg(char **cmd)
{
	int	i;
	int	nb;

	i = -1;
	if (*cmd != NULL && cmd[1] != NULL)
	{
		while (cmd[1][++i])
			if (ft_isdigit(cmd[1][i]) == FALSE)
				return (exit_output(cmd, 2));
		nb = ft_atoi(cmd[1]);
		return (nb % 256);
		if (cmd[2] != NULL)
			return (exit_output(cmd, 1));
	}
	return (0);
}


int main(int ac, char **av)
{
	(void)ac;
	int nb;
	nb = exit_arg(av);
	exit (nb);
}