/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 21:40:56 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/02 12:03:28 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

typedef struct s_scanner
{
	const char	*start; //start of the line
	const char	*current; //current position in the line
}	t_scanner;

typedef enum e_tok_type
{
	TOK_WORD, //word
	TOK_PIPE, //pipe
	TOK_LESS, // [ < ]
	TOK_GREAT, // [ > ]
	TOK_DLESS, // [ << ]
	TOK_DGREAT, // [ >> ]
	TOK_OR_IF, // [ || ]
	TOK_AND_IF,// [ && ]
	TOK_LPAREN, // [ ( ]
	TOK_RPAREN, // [ ) ]
	TOK_EOF, //end of file
	TOK_ERROR, //error
}	t_tok_type;

typedef struct s_token
{
	t_tok_type	type; //type of token
	char		*value; //value of token
}	t_token;

void		init_scanner(t_scanner *scanner, const char *line);
t_token		scan_token(t_scanner *self);
t_token		match_next(char expect, t_tok_type iftrue, t_tok_type iffalse,
				t_scanner *s);
#endif