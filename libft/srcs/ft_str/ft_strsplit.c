/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:00:43 by jdugoudr          #+#    #+#             */
/*   Updated: 2018/12/09 15:37:13 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlentoc(char const *s, char c)
{
	int	i;

	i = 0;
	while (*(s + i) != c && *(s + i) != '\0')
		i += 1;
	return (i);
}

static int	ft_cpysplit(char **r, char const *s, char c, int w)
{
	int		len;
	char	*wr;
	int		res;

	len = 0;
	wr = NULL;
	if (*s == '\0')
		return (1);
	if (*s == c)
		return (ft_cpysplit(r, s + 1, c, w));
	len = ft_strlentoc(s, c);
	wr = ft_strnew(len);
	if (wr == NULL)
		return (-1);
	*(r + w) = ft_strncpy(wr, s, len);
	w = w + 1;
	if ((res = ft_cpysplit(r, s + len, c, w)) < 0)
	{
		free(wr);
		return (-1);
	}
	return (0);
}

static int	ft_countword(char const *s, char c)
{
	int	i;
	int	cmpts;
	int	onew;

	onew = 0;
	cmpts = 0;
	i = 0;
	while (*(s + i) != '\0')
	{
		while (*(s + i) == c)
			i += 1;
		while (*(s + i) != c && *(s + i) != '\0')
		{
			i += 1;
			onew += 1;
		}
		if (onew != 0)
			cmpts += 1;
		onew = 0;
	}
	return (cmpts);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**r;
	int		cmpts;
	int		res;

	res = 0;
	r = NULL;
	if (s == NULL)
		return (NULL);
	cmpts = ft_countword(s, c);
	r = (char **)ft_memalloc((cmpts + 1) * sizeof(char *));
	if (r == NULL)
		return (NULL);
	*(r + cmpts) = NULL;
	res = ft_cpysplit(r, s, c, 0);
	if (res < 0)
	{
		free(r);
		return (NULL);
	}
	return (r);
}
