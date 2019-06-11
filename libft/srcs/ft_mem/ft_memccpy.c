/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:29:16 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/12 10:25:42 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char		*dest;
	const char	*source;
	char		cc;

	dest = (char *)dst;
	source = (const char *)src;
	cc = (char)c;
	while (n-- > 0)
	{
		*dest++ = *source;
		if (cc == *source)
			return (dest);
		source++;
	}
	return (NULL);
}
