/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 21:40:56 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/07/11 17:39:05 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

typedef struct s_scanner //scanner: starting and current position
{
	const char	*start;   //start of the string
	const char	*current; //current character of the string
}	t_scanner;

typedef enum e_tok_type //type of the token
{
	TOK_WORD,    //token of a word
	TOK_PIPE,    //token of a [ | ]
	TOK_LESS,    //token of a [ < ]
	TOK_GREAT,   //token of a [ > ]
	TOK_DLESS,   //token of a [ << ]
	TOK_DGREAT,  //token of a [ >> ]
	TOK_OR_IF,   //token of a [ || ]
	TOK_AND_IF,  //token of a [ && ]
	TOK_LPAREN,  //token of a [ ( ]
	TOK_RPAREN,  //token of a [ ) ]
	TOK_EOF,     //token of end of file
	TOK_ERROR,   //token of an error
}	t_tok_type;

typedef struct s_token //token: type and value
{
	t_tok_type	type;   //type of the token
	char		*value; //value of the token
}	t_token;

void		init_scanner(t_scanner *scanner, const char *line);
t_token		scan_token(t_scanner *self);
t_token		match_next(char expect, t_tok_type iftrue, t_tok_type iffalse,
				t_scanner *s);
#endif