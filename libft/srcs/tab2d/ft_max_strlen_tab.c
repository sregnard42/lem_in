/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max_strlen_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 12:44:20 by sregnard          #+#    #+#             */
/*   Updated: 2018/12/14 12:50:03 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_max_strlen_tab(char **tab)
{
	int	max;
	int	len;

	max = 0;
	while (tab && *tab)
	{
		len = ft_strlen(*tab++);
		if (max < len)
			max = len;
	}
	return (max);
}
