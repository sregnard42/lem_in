/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:29:54 by sregnard          #+#    #+#             */
/*   Updated: 2019/02/13 16:20:16 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	pf_base(const char c)
{
	if (c == 'o' || c == 'O')
		return (8);
	if (c == 'x' || c == 'X' || c == 'p')
		return (16);
	return (10);
}

unsigned int	pf_atoi(const char *s)
{
	unsigned int nb;

	nb = 0;
	while (ft_isdigit(*s))
		nb = nb * 10 + *s++ - '0';
	return (nb);
}

unsigned int	pf_itoa(t_printf *p, long double nbr)
{
	long long unsigned	nb;
	size_t				len;
	char				c;

	nb = nbr;
	len = 0;
	if (nb >= 10)
		len += pf_itoa(p, nb / 10);
	nb %= 10;
	c = nb + '0';
	len += pf_buffer(p, &c, 1);
	return (len);
}

char			*pf_prefix(t_printf *p, long double nb, unsigned int base)
{
	if (p->flags & FLAG_NEGATIVE)
		return ("-");
	if (p->flags & FLAG_POSITIVE && p->flags & FLAG_PLUS)
		return ("+");
	if (p->flags & FLAG_POSITIVE && p->flags & FLAG_SPACE)
		return (" ");
	if (*p->format == 'f')
		return (0);
	if (*p->format == 'p')
		return ("0x");
	if (p->flags & FLAG_HASH && base == 8
			&& ((p->flags & FLAG_PRECISION && p->precision == 0)
			|| (!(p->flags & FLAG_PRECISION) && nb != 0)))
		return ("0");
	if ((p->flags & FLAG_HASH && base == 16 && nb != 0))
	{
		if (*p->format == 'x')
			return ("0x");
		if (*p->format == 'X')
			return ("0X");
	}
	return (0);
}

int				pf_flags_extra(t_printf *p)
{
	if (*p->format == 'j')
	{
		++p->format;
		return (p->flags |= FLAG_INTMAX_T);
	}
	if (*p->format == 'z')
	{
		++p->format;
		return (p->flags |= FLAG_SIZE_T);
	}
	return (0);
}
