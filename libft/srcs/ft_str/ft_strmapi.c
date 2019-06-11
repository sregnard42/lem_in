/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 10:23:49 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/14 10:47:41 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	char	*p;
	int		size;
	int		i;

	if (!(s && f && *f))
		return (NULL);
	size = ft_strlen(s);
	if ((str = ft_strnew(size)) == NULL)
		return (NULL);
	p = str;
	i = 0;
	while (*s)
		*str++ = f(i++, *s++);
	return (p);
}
