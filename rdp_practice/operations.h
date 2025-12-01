/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:27:42 by tkok-kea          #+#    #+#             */
/*   Updated: 2024/06/15 15:54:26 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

typedef enum e_ops
{
	OP_PLUS,
	OP_MINUS,
	OP_MULT,
	OP_DIV,
	OP_POW
}	t_ops;

typedef int	(*t_operation)(int, int);

int	plus(int x, int y);
int	minus(int x, int y);
int	multiply(int x, int y);
int	divide(int x, int y);
int	power(int x, int y);

#endif