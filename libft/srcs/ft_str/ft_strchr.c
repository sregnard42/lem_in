/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:42:37 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/14 10:51:08 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
		if (*s == (unsigned char)c)
			return ((char *)s);
		else
			s++;
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}
