/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:42:26 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/12 10:44:14 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t src_len;

	src_len = ft_strlen(src);
	if (src_len < len)
	{
		ft_memset(dst + src_len, '\0', len - src_len);
		ft_memcpy(dst, src, src_len);
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
