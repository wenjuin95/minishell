/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:39:34 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/04 16:43:16 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	tok_is_redirection(t_tok_type type)
{
	return (type == TOK_GREAT || type == TOK_LESS || type == TOK_DGREAT
		|| type == TOK_DLESS);
}

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

void	add_to_redir_list(t_list **redir_list, t_parser *parser)
{
	t_redir_data	*new_data;

	new_data = malloc(sizeof(t_redir_data));
	new_data->type = parser->next_token.type;
	advance_psr(parser);
	if (parser->next_token.type == TOK_WORD)
	{
		new_data->value = ft_strdup(parser->next_token.value);
		ft_lstadd_back(redir_list, ft_lstnew((void *)new_data));
		advance_psr(parser);
	}
	else
		printf("Syntax Error near %s", parser->next_token.value);

}

void	parse_prefix(t_list **redir_list, t_parser *parser)
{
	while (tok_is_redirection(parser->next_token.type))
	{
		add_to_redir_list(redir_list, parser);
	}
}

void	parse_suffix(t_dym_arr *arr, t_list **redir_list, t_parser *parser)
{
	while (parser->next_token.type == TOK_WORD || tok_is_redirection(parser->next_token.type))
	{
		if (parser->next_token.type == TOK_WORD)
		{
			add_to_array(arr, parser->next_token.value);
			advance_psr(parser);
		}
		else
		{
			add_to_redir_list(redir_list, parser);
		}
	}
}

t_cmd	*parse_command(t_parser *parser)
{
	t_exec_cmd	*cmd;
	t_dym_arr	argv_dym;
	t_list		*redir_list;

	redir_list = NULL;
	argv_dym.capacity = 0;
	argv_dym.size = 0;
	argv_dym.arr = NULL;
	parse_prefix(&redir_list, parser);
	if (parser->next_token.type == TOK_WORD)
	{
		add_to_array(&argv_dym, parser->next_token.value);
		advance_psr(parser);
	}
	parse_suffix(&argv_dym, &redir_list, parser);
	add_to_array(&argv_dym, NULL);
	cmd = malloc(sizeof(t_exec_cmd));
	cmd->type = CMD_EXEC;
	cmd->argv = argv_dym.arr;
	cmd->redir_list = redir_list;
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
