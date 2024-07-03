/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:39:34 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/03 14:05:52 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	@brief Check if token is a redirection
**	@param type Token type
*/
bool	tok_is_redirection(t_tok_type type)
{
	return (type == TOK_GREAT || type == TOK_LESS || type == TOK_DGREAT
		|| type == TOK_DLESS);
}

/*
*	@brief Add new string to dynamic array
*	@param array Dynamic array
*	@param new New string to add
*/
void	add_to_array(t_dym_arr *array, const char *new)
{
	int		new_capacity;
	char	**new_array;

	if (array->capacity == 0) //if capacity is 0, allocate memory for 1 string
	{
		array->capacity = 1;
		array->arr = malloc(sizeof(char *));
		if (array->arr == NULL)
		{
			perror("Malloc");
			exit(EXIT_FAILURE);
		}
	}
	else if (array->size >= array->capacity) //if size is more than capacity, double the capacity
	{
		new_capacity = array->capacity * 2; //double the capacity
		new_array = malloc(new_capacity * sizeof(char *));
		ft_memmove(new_array, array->arr, (array->capacity * sizeof(char *))); //copy old array to new array
		free(array->arr); //free old array
		array->arr = new_array; //assign new array to old array
		array->capacity = new_capacity; //assign new capacity to old capacity
	}
	array->arr[array->size] = ft_strdup(new); //add new string to array
	array->size++; //increment size
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

/*
*	@brief Parse command with redirection and arguments
*	@param parser Parser
*	@return t_cmd* Command node
*/
t_cmd	*parse_command(t_parser *parser)
{
	t_exec_cmd	*cmd;
	t_cmd		*rcmd;
	t_dym_arr	argv_dym;
	t_list		*redir_list;

	redir_list = NULL; //initialize redirection list
	argv_dym.capacity = 0; //initialize capacity
	argv_dym.size = 0; //initialize size
	argv_dym.arr = NULL; //initialize array
	parse_prefix(&redir_list, parser); //parse prefix
	if (parser->next_token.type == TOK_WORD) //if token type is word, add to array
	{
		add_to_array(&argv_dym, parser->next_token.value);
		advance_psr(parser); //advance to next token
	}
	parse_suffix(&argv_dym, &redir_list, parser); //parse suffix
	add_to_array(&argv_dym, NULL); //add NULL to the last array
	cmd = malloc(sizeof(t_exec_cmd)); //allocate memory for command node
	cmd->type = CMD_EXEC; //assign command type
	cmd->argv = argv_dym.arr; //assign array to command node
	if (redir_list != NULL) //if redirect list is not empty, assign to redirect command
	{
		rcmd = redir_cmd(redir_list, (t_cmd *)cmd);
		return ((t_cmd *)rcmd);
	}
	return ((t_cmd *)cmd); //return command node
}

/*
*	@brief Parse pipeline
*	@param parser Parser
*	@return t_cmd* Command node
*/
t_cmd	*parse_pipeline(t_parser *parser)
{
	t_cmd		*cmd;
	t_pipe_cmd	*temp;

	ft_printf("go parse pipeline\n"); //debug
	cmd = parse_command(parser); //parse command
	ft_printf("\ncommand type: %d\n", cmd->type); //debug //seg fault here
	while (parser->next_token.type == TOK_PIPE) //if token type is pipe then parse pipeline
	{
		temp = malloc(sizeof(t_pipe_cmd));
		temp->type = CMD_PIPE;
		temp->left_cmd = cmd;
		advance_psr(parser); //advance to next token
		temp->right_cmd = parse_command(parser);
		cmd = (t_cmd *)temp;
	}
	return (cmd);
}

/*
*	@brief Initialize parser
*	@param line Line to parse
*/
void	parse(const char *line)
{
	t_parser	parser;
	t_cmd		*cmd_tree;

	init_parser(&parser, line); //initialize parser with line
	ft_printf("Parsing: %s\n", line); //debug
	ft_printf("Scanner start: %s\n", parser.scanner.start); //debug
	ft_printf("Scanner current: %s\n", parser.scanner.current); //debug
	ft_printf("Next token type: %d\n", parser.next_token.type); //debug
	ft_printf("Next token: %s\n", parser.next_token.value); //debug
	cmd_tree = parse_pipeline(&parser); //parse pipeline and assign to command tree
	eval_tree(cmd_tree); //evaluate command tree
	free_tree(cmd_tree); //free command tree
}
