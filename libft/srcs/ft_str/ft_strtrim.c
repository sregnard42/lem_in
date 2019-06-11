/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 10:40:15 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/14 10:41:49 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_strlen_trimmed(char const *s)
{
	int	len;

	len = 0;
	while (ft_isspace(*s))
		s++;
	while (*s++)
		len++;
	s -= 2;
	while (*s && ft_isspace(*s) && len > 0)
	{
		len--;
		s--;
	}
	return (len);
}

char		*ft_strtrim(char const *s)
{
	char	*str;
	int		len;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen_trimmed(s);
	if ((str = ft_strnew(len)) == NULL)
		return (NULL);
	while (ft_isspace(*s))
		s++;
	while (*s && i < len)
		str[i++] = *s++;
	str[i] = '\0';
	return (str);
}
