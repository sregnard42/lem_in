/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:59:24 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/13 16:27:14 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(const char *str)
{
	char	*rev;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	rev = ft_strnew(len);
	while (len > 0)
		rev[i++] = str[--len];
	rev[i] = '\0';
	return (rev);
}
