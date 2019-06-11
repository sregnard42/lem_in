/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:41:00 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/14 14:40:49 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest;
	const char	*source;

	dest = (char *)dst;
	source = (const char *)src;
	if (source < dest && source + len > dest)
	{
		source += len - 1;
		dest += len - 1;
		while (len-- > 0)
			*dest-- = *source--;
	}
	else
		while (len-- > 0)
			*dest++ = *source++;
	return (dst);
}
