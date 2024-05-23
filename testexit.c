// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>

#include "libft/libft.h"

# define TRUE 1
# define FALSE 0

int check_digit(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	exit_check(char **cmd)
{
	if (cmd[1] != NULL && cmd[2] != NULL)
	{
		if (check_digit(cmd[1]) == TRUE)
		{
			ft_printf("exit\nminishell: exit: %s: numeric argument required\n",
				cmd[1]);
			exit(1);
		}
		else
		{
			ft_printf("exit\nminishell: exit: too many arguments\n");
		}
	}
	else if (cmd[1] != NULL && check_digit(cmd[1]) == TRUE)
	{
		ft_printf("exit\nminishell: exit: %s: numeric argument required\n",
			cmd[1]);
		exit(1);
	}
	else
	{
		ft_printf("exit\n");
		exit(0);
	}
}

void	exit_cmd(char **cmd)
{
	if (cmd[1] != NULL)
	{
		exit_check(cmd);
		exit(ft_atoi(cmd[1]));
	}
	else
	{
		ft_printf("exit\n");
		exit(0);
	}
}



int main(int ac, char **av)
{
	(void)ac;
	exit_cmd(av);
	return (0);
}