/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 10:15:40 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/14 10:47:49 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	char	*p;
	int		size;

	if (!(s && f && *f))
		return (NULL);
	size = ft_strlen(s);
	if ((str = ft_strnew(size)) == NULL)
		return (NULL);
	p = str;
	while (*s)
		*str++ = f(*s++);
	return (p);
}
