/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:04:47 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/08 17:11:25 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char *str;
	char cc;

	str = (char *)s;
	cc = (char)c;
	while (n > 0)
	{
		if (*str == cc)
			return (str);
		str++;
		n--;
	}
	return (NULL);
}
