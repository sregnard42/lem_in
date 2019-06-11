/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 11:37:34 by sregnard          #+#    #+#             */
/*   Updated: 2018/12/14 12:47:42 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			*ft_atoi_tab(char **src, int size)
{
	int	*tab;
	int	i;

	if (!src || !(tab = (int *)malloc(sizeof(int) * size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		tab[i] = ft_atoi(src[i]);
		i++;
	}
	return (tab);
}
