/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:05:56 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/02 10:18:20 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parser(t_parser *parser, const char *line)
{
	init_scanner(&parser->scanner, line);
	parser->next_token = scan_token(&parser->scanner);
}

static void	free_token(t_token token)
{
	if (token.type != TOK_EOF)
		free(token.value);
}

void	advance_psr(t_parser *parser)
{
	free_token(parser->next_token);
	parser->next_token = scan_token(&parser->scanner);
}

void	free_double(char **arr)
{
	char	**s_ptr;

	s_ptr = arr;
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(s_ptr);
}

void	free_tree(t_cmd *node)
{
	t_exec_cmd	*ecmd;
	t_redir_cmd	*rcmd;
	t_pipe_cmd	*pcmd;

	if (node->type == CMD_EXEC)
	{
		ecmd = (t_exec_cmd *)node;
		free_double(ecmd->argv);
	}
	else if (node->type == CMD_REDIR)
	{
		rcmd = (t_redir_cmd *)node;
		free_tree(rcmd->next_cmd);
		ft_lstclear(&rcmd->redir_list, free_redir_data);
		free(rcmd->redir_list);
	}
	else if (node->type == CMD_PIPE)
	{
		pcmd = (t_pipe_cmd *)node;
		free_tree(pcmd->left_cmd);
		free_tree(pcmd->right_cmd);
	}
	free(node);
}

/* FOR DEBUG */

/* void	print_token(t_token token)
{
	printf("%2d ", token.type);
	if (token.type == TOK_EOF)
		printf("EOF\n");
	else
		printf("'%s'\n", token.value);
} */