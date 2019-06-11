/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:43:49 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/14 13:17:24 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int n)
{
	unsigned int	nb;
	int				len;

	len = 1;
	if (n < 0)
	{
		len++;
		nb = -n;
	}
	else
		nb = n;
	while (nb >= 10)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	unsigned int	nb;
	char			*s;
	int				len;

	if (n == 0)
		return (ft_strdup("0"));
	len = ft_nbrlen(n);
	if ((s = ft_strnew(len)) == NULL)
		return (NULL);
	if (n < 0)
	{
		s[0] = '-';
		nb = -n;
	}
	else
		nb = n;
	s[len--] = '\0';
	while (nb > 0)
	{
		s[len--] = nb % 10 + '0';
		nb /= 10;
	}
	return (s);
}
