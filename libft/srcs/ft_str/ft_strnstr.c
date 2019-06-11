/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:17:52 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/12 13:57:40 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	needle_found(const char *src, const char *needle, size_t len)
{
	while (*src && *needle && len-- > 0)
		if (*src++ != *needle++)
			return (0);
	if (*needle)
		return (0);
	return (1);
}

char		*ft_strnstr(const char *src, const char *needle, size_t len)
{
	while (*src && len > 0)
		if (needle_found(src++, needle, len--) == 1)
			return ((char *)--src);
	return (0);
}
