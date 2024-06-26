/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 21:40:56 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/26 11:26:41 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

typedef struct s_scanner
{
	const char	*start;
	const char	*current;
}	t_scanner;

typedef enum e_ttype
{
	TOK_WORD,
	TOK_PIPE,
	TOK_LESS,
	TOK_GREAT,
	TOK_DLESS,
	TOK_DGREAT,
	TOK_OR_IF,
	TOK_AND_IF,
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_EOF,
	TOK_ERROR,
}	t_ttype;

typedef struct s_token
{
	t_ttype	type;
	char	*value;
}	t_token;

void		init_scanner(t_scanner *scanner, const char *line);
t_token		scan_token(t_scanner *self);
t_token		match_next(
				char expect, t_ttype iftrue, t_ttype iffalse, t_scanner *s);
#endif