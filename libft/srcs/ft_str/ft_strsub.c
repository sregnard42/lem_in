/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 10:32:57 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/14 10:42:32 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*p;

	if ((str = ft_strnew(len)) == NULL || s == NULL)
		return (NULL);
	p = str;
	while (*s && len-- > 0)
		*str++ = *(s++ + start);
	*str = '\0';
	return (p);
}
