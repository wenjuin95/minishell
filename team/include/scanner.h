/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 21:40:56 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/28 11:29:34 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

typedef struct s_scanner
{
	const char	*start; //start of the line
	const char	*current; //current position
}	t_scanner;

typedef enum e_ttype //token type
{
	TOK_WORD, //word
	TOK_PIPE, //pipe
	TOK_LESS, //less than
	TOK_GREAT, //greater than
	TOK_DLESS, //double less than
	TOK_DGREAT, //double greater than
	TOK_OR_IF, //or if
	TOK_AND_IF, //and if
	TOK_LPAREN, //left parenthesis
	TOK_RPAREN, //right parenthesis
	TOK_EOF, //end of file
	TOK_ERROR, //error
}	t_ttype;

typedef struct s_token
{
	t_ttype	type; //type of token
	char	*value; //value of token
}	t_token;

void		init_scanner(t_scanner *scanner, const char *line);
t_token		scan_token(t_scanner *self);
t_token		match_next(
				char expect, t_ttype iftrue, t_ttype iffalse, t_scanner *s);
#endif