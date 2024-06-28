/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:39:34 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/27 17:26:29 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_array(t_dym_arr *array, const char *new)
{
	int		new_capacity;
	char	**new_array;

	if (array->capacity == 0)
	{
		array->capacity = 1;
		array->arr = malloc(sizeof(char *));
		if (array->arr == NULL)
		{
			perror("Malloc");
			exit(EXIT_FAILURE);
		}
	}
	else if (array->size >= array->capacity)
	{
		new_capacity = array->capacity * 2;
		new_array = malloc(new_capacity * sizeof(char *));
		ft_memmove(new_array, array->arr, (array->capacity * sizeof(char *)));
		free(array->arr);
		array->arr = new_array;
		array->capacity = new_capacity;
	}
	array->arr[array->size] = ft_strdup(new);
	array->size++;
}

t_cmd	*parse_command(t_parser *parser)
{
	t_exec_cmd	*cmd;
	t_dym_arr	argv_dym;

	argv_dym.capacity = 0;
	argv_dym.size = 0;
	argv_dym.arr = NULL;
	if (parser->next_token.type == TOK_WORD)
	{
		add_to_array(&argv_dym, parser->next_token.value);
		advance_psr(parser);
	}
	while (parser->next_token.type == TOK_WORD)
	{
		add_to_array(&argv_dym, parser->next_token.value);
		advance_psr(parser);
	}
	add_to_array(&argv_dym, NULL);
	cmd = malloc(sizeof(t_exec_cmd));
	cmd->type = CMD_EXEC;
	cmd->argv = argv_dym.arr;
	return ((t_cmd *)cmd);
}

t_cmd	*parse_pipeline(t_parser *parser)
{
	t_cmd		*cmd;
	t_pipe_cmd	*temp;

	cmd = parse_command(parser);
	while (parser->next_token.type == TOK_PIPE)
	{
		temp = malloc(sizeof(t_pipe_cmd));
		temp->type = CMD_PIPE;
		temp->left_cmd = cmd;
		advance_psr(parser);
		temp->right_cmd = parse_command(parser);
		cmd = (t_cmd *)temp;
	}
	return (cmd);
}

void	parse(const char *line)
{
	t_parser	parser;
	t_cmd		*cmd_tree;

	init_parser(&parser, line);
	cmd_tree = parse_pipeline(&parser);
	eval_tree(cmd_tree);
	free_tree(cmd_tree);
}
