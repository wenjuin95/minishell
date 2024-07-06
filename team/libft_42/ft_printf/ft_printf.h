/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 00:57:51 by tkok-kea          #+#    #+#             */
/*   Updated: 2023/12/30 21:43:15 by tkok-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

/*Different results of %p when it is NULL */
# ifdef __linux__
#  define NULLPTR "(nil)"
# elif __APPLE__
#  define NULLPTR "0x0"
# endif

/*Specifier and hexadecimal symbols*/
# define SPECIFIER	"cspdiuxX%"
# define HEXLOW		"0123456789abcdef"
# define HEXUP		"0123456789ABCDEF"

typedef struct s_flags
{
	int		hash;
	int		zero;
	int		left;
	int		space;
	int		plus;
	int		width;
	int		dot;
	int		precision;
	char	spec;
}	t_flags;

/* Main printf and sub functions for each specifier */
int		ft_printf(const char *format, ...);
int		print_char(va_list args, t_flags flags);
int		print_string(va_list args, t_flags flags);
int		print_ptr(va_list args, t_flags flags);
int		print_dec(va_list args, t_flags fl);
int		print_u(va_list args, t_flags fl);
int		print_hex(va_list args, t_flags fl);

/* String printing functions */
int		ft_putchar2(char c);
int		ft_putstr2(char *s);
int		ft_putstr_prec(char *s, int preci);
int		put_padding(int start, int end, int zero);

/* fucntions to set flag */
t_flags	set_flag(char *s);
void	print_flags(t_flags flags);
t_flags	new_flag(void);

char	*ft_str_chr(const char *s, int c);
int		ft_is_digit(int c);
size_t	ft_str_len(char *s);
int		dec_len(unsigned int u);

#endif