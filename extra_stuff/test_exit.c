#include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

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

int exit_option(char **cmd)
{
	int	i;
	int	nb;

	if (*cmd != NULL && ft_strncmp(*cmd, "./a.out", 8) != 0)
		return (0);
	i = -1;
	if (cmd[1] != NULL)
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
	nb = exit_option(av);
	exit (nb);
}