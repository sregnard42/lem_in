/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:58:47 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/12 11:45:18 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	needle_found(const char *haystack, const char *needle)
{
	while (*haystack && *needle)
		if (*haystack++ != *needle++)
			return (0);
	if (*needle)
		return (0);
	return (1);
}

char		*ft_strstr(const char *haystack, const char *needle)
{
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (*haystack)
		if (needle_found(haystack++, needle) == 1)
			return ((char *)--haystack);
	return (0);
}
