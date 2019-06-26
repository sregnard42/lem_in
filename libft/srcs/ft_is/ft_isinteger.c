/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinteger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:47:24 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/26 11:25:48 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_isinteger(char *s)
{
	int				sign;
	unsigned int	nb;

	if (!s || !ft_isnumber(s))
		return (0);
	nb = 0;
	while (ft_isspace(*s))
		++s;
	sign = (*s == '-') ? -1 : 1;
	(*s == '-' || *s == '+') ? ++s : 0;
	while (ft_isdigit(*s) && nb < INT_MAX)
		nb = (nb * 10) + *s++ - '0';
	return (sign == 1 ? nb <= INT_MAX : nb <= (unsigned int)INT_MAX + 1);
}
