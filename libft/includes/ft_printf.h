/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 17:20:07 by sregnard          #+#    #+#             */
/*   Updated: 2019/02/20 00:18:02 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <float.h>
# include <limits.h>

# define PF_BUFF_SIZE	256

/*
**	----------------------------------------------------------------------
*/

typedef struct		s_printf
{
	char			*format;
	va_list			ap;
	char			buf[PF_BUFF_SIZE];
	unsigned int	index;
	unsigned int	flags;
	unsigned int	width;
	unsigned int	precision;
	unsigned int	written;
}					t_printf;

/*
**	----------------------------------------------------------------------
*/

enum				e_printf_flags
{
	FLAG_0 = (1 << 0),
	FLAG_LEFT_ALIGN = (1 << 2),
	FLAG_PLUS = (1 << 3),
	FLAG_SPACE = (1 << 4),
	FLAG_HASH = (1 << 5),
	FLAG_WIDTH = (1 << 6),
	FLAG_PRECISION = (1 << 7),
	FLAG_CHAR = (1 << 8),
	FLAG_SHORT = (1 << 9),
	FLAG_LONG = (1 << 10),
	FLAG_LONG_LONG = (1 << 11),
	FLAG_FLOAT = (1 << 12),
	FLAG_DOUBLE = (1 << 13),
	FLAG_LONG_DOUBLE = (1 << 14),
	FLAG_INTMAX_T = (1 << 15),
	FLAG_SIZE_T = (1 << 16),
	FLAG_NEGATIVE = (1 << 17),
	FLAG_POSITIVE = (1 << 18),
};

/*
**	----------------------------------------------------------------------
**	ft_printf.c
*/

int					ft_printf(const char *format, ...);
int					pf_buffer(t_printf *p, const char *s, size_t len);
int					pf_padding(t_printf *p, size_t len);

/*
**	----------------------------------------------------------------------
**	ft_args.c
*/

int					pf_parse_args(t_printf *p);

/*
**	----------------------------------------------------------------------
**	ft_chars.c
*/

int					pf_putchar(t_printf *p, const char c);
int					pf_putstr(t_printf *p, const char *s);

/*
**	----------------------------------------------------------------------
**	ft_numbers.c
*/

int					pf_nb_signed(t_printf *p);
int					pf_nb_unsigned(t_printf *p);
int					pf_nbrlen(t_printf *p, long double nb, unsigned int base);
int					pf_nbrpad(t_printf *p, long double nb, unsigned int base);

/*
**	----------------------------------------------------------------------
**	ft_floats.c
*/

int					pf_floats(t_printf *p);

/*
**	----------------------------------------------------------------------
**	ft_utils.c
*/

unsigned int		pf_base(const char c);
unsigned int		pf_atoi(const char *s);
unsigned int		pf_itoa(t_printf *p, long double nb);
char				*pf_prefix(t_printf *p, long double nb, unsigned int base);
int					pf_flags_extra(t_printf *p);

#endif
