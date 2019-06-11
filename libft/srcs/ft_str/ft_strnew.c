/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 09:30:19 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/11 16:22:59 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*s;
	size_t	i;

	size += 1;
	if ((s = (char *)ft_memalloc(sizeof(char) * size)) == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		s[i++] = '\0';
	return (s);
}
