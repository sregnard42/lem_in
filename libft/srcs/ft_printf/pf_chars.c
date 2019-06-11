/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_chars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 17:59:04 by sregnard          #+#    #+#             */
/*   Updated: 2019/02/13 12:56:07 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_putchar(t_printf *p, const char c)
{
	pf_padding(p, 1);
	return (pf_buffer(p, &c, 1));
}

int	pf_putstr(t_printf *p, const char *s)
{
	size_t	len;

	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	if (p->flags & FLAG_PRECISION)
		p->precision < len ? len = p->precision : 0;
	pf_padding(p, len);
	return (pf_buffer(p, s, len));
}
