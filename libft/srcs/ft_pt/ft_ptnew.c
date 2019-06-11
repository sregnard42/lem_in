/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptnew.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 14:20:56 by sregnard          #+#    #+#             */
/*   Updated: 2018/12/19 14:21:06 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

t_point	*ft_ptnew(int x, int y, int z)
{
	t_point	*pt;

	pt = (t_point *)malloc(sizeof(t_point));
	ft_ptset(pt, x, y, z);
	return (pt);
}
