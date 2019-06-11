/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinteger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:47:24 by sregnard          #+#    #+#             */
/*   Updated: 2019/04/07 13:46:41 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_isinteger(char *s)
{
	unsigned int	nb;

	if (!s || !ft_isnumber(s))
		return (0);
	nb = 0;
	while (ft_isspace(*s))
		++s;
	(*s == '-' || *s == '+') ? ++s : 0;
	while (ft_isdigit(*s) && nb < INT_MAX)
		nb = (nb * 10) + *s++ - '0';
	return (nb <= INT_MAX);
}
