/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 15:48:27 by sregnard          #+#    #+#             */
/*   Updated: 2019/02/13 16:04:46 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pf_conversion(t_printf *p)
{
	char	c;

	c = *p->format;
	if (c == 'c')
		return (pf_putchar(p, va_arg(p->ap, unsigned int)));
	if (c == 's')
		return (pf_putstr(p, va_arg(p->ap, char *)));
	if (c == 'd' || c == 'i')
		return (pf_nb_signed(p));
	if (c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x' || c == 'X'
			|| c == 'p')
		return (pf_nb_unsigned(p));
	if (c == 'f')
		return (pf_floats(p));
	if (c == '%')
		return (pf_putchar(p, '%'));
	if (c)
		return (pf_putchar(p, c));
	return (0);
}

static int	pf_flags(t_printf *p)
{
	if (*p->format == 'h')
	{
		if (*++p->format == 'h')
		{
			++p->format;
			return (p->flags |= FLAG_CHAR);
		}
		return (p->flags |= FLAG_SHORT);
	}
	if (*p->format == 'l')
	{
		if (*++p->format == 'l')
		{
			++p->format;
			return (p->flags |= FLAG_LONG_LONG);
		}
		return (p->flags |= FLAG_LONG);
	}
	if (*p->format == 'L')
	{
		++p->format;
		return (p->flags |= FLAG_LONG_DOUBLE);
	}
	return (pf_flags_extra(p));
}

static int	pf_width_precision(t_printf *p)
{
	if (*p->format >= '1' && *p->format <= '9')
	{
		p->width = pf_atoi(p->format++);
		p->flags |= FLAG_WIDTH;
		while (*p->format >= '0' && *p->format <= '9')
			++(p->format);
	}
	if (*p->format == '.')
	{
		p->precision = pf_atoi(++p->format);
		p->flags |= FLAG_PRECISION;
		while (*p->format >= '0' && *p->format <= '9')
			++(p->format);
	}
	return (1);
}

static int	pf_options(t_printf *p)
{
	if (*p->format == '#')
		return (p->flags |= FLAG_HASH);
	if (*p->format == '+')
	{
		p->flags & FLAG_SPACE ? p->flags &= ~FLAG_SPACE : 0;
		return (p->flags |= FLAG_PLUS);
	}
	if (*p->format == ' ')
	{
		if (p->flags & FLAG_PLUS)
			return (1);
		return (p->flags |= FLAG_SPACE);
	}
	if (*p->format == '-')
	{
		p->flags & FLAG_0 ? p->flags &= ~FLAG_0 : 0;
		return (p->flags |= FLAG_LEFT_ALIGN);
	}
	if (*p->format == '0')
	{
		if (p->flags & FLAG_LEFT_ALIGN)
			return (1);
		return (p->flags |= FLAG_0);
	}
	return (0);
}

int			pf_parse_args(t_printf *p)
{
	p->flags = 0;
	p->width = 0;
	p->precision = 0;
	++(p->format);
	if (*p->format == '%')
		return (pf_putchar(p, '%'));
	while (pf_options(p))
		++(p->format);
	pf_width_precision(p);
	pf_flags(p);
	pf_conversion(p);
	pf_padding(p, 0);
	return (1);
}
