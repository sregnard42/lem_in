/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_floats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:51:07 by sregnard          #+#    #+#             */
/*   Updated: 2019/02/15 12:40:22 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pf_add_zeros(t_printf *p, long double nb)
{
	size_t	len;

	len = 0;
	while (nb > 0.0f && nb < 0.1f && ++len < p->precision)
	{
		nb *= 10;
		pf_buffer(p, "0", 1);
	}
	return (len);
}

static int	pf_precision(t_printf *p, long double nb)
{
	size_t	i;
	size_t	len;

	if (p->precision == 0)
		return (0);
	nb -= (unsigned long long)nb;
	pf_buffer(p, ".", 1);
	len = pf_add_zeros(p, nb);
	i = 0;
	while (i++ < p->precision && nb * 10 <= ULLONG_MAX)
		nb *= 10;
	if (nb - (unsigned long long)nb >= 0.5)
		nb += 1;
	i = pf_itoa(p, nb);
	while (i++ < p->precision - len)
		pf_buffer(p, "0", 1);
	return (0);
}

static int	pf_ftoa(t_printf *p, long double nb)
{
	size_t	len;

	if (p->flags & FLAG_LEFT_ALIGN)
		len = pf_nbrlen(p, nb, 10);
	pf_itoa(p, nb);
	pf_precision(p, nb);
	if (p->flags & FLAG_LEFT_ALIGN)
		return (pf_padding(p, len));
	return (0);
}

int			pf_floats(t_printf *p)
{
	long double		nb;

	!(p->flags & FLAG_PRECISION) ? p->precision = 6 : 0;
	if (p->flags & FLAG_LONG_DOUBLE)
		nb = va_arg(p->ap, long double);
	else
		nb = va_arg(p->ap, double);
	(nb < 0) ? (p->flags |= FLAG_NEGATIVE) : (p->flags |= FLAG_POSITIVE);
	(nb < 0) ? (nb = -nb) : 0;
	if (nb >= ULLONG_MAX)
	{
		p->flags &= ~FLAG_PRECISION;
		p->flags &= ~FLAG_0;
		if (p->flags & FLAG_POSITIVE)
			return (pf_putstr(p, "inf"));
		return (pf_putstr(p, "-inf"));
	}
	pf_nbrpad(p, nb, 10);
	return (pf_ftoa(p, nb));
}
