#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void history(void)
{
	HIST_ENTRY **list;
	int i;

	list = history_list();
	if (list)
	{
		i = 0;
		while (list[i])
		{
			printf("%d %s\n", i + history_base, list[i]->line);
			i++;
		}
	}
}

void check_input(char *input)
{
	if (strcmp(input, "history") == 0) //if "history" execute history list
		history();
	if (strcmp(input, "exit") == 0) //if "exit" execute exit
		exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	(void)av;
	char *input;

	if (ac > 1)
	{
		printf("no arguments needed\n");
		return (1);
	}
	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL) //if ctrl + D
			exit(EXIT_SUCCESS);
		add_history(input); //add to history
		check_input(input); //check token
	}
	return (0);
}
