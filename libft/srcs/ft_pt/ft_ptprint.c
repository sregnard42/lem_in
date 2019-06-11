/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 08:43:35 by sregnard          #+#    #+#             */
/*   Updated: 2018/12/29 14:15:12 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ptprint(t_point *pt)
{
	ft_putchar('(');
	ft_putnbr(pt->x);
	ft_putstr(", ");
	ft_putnbr(pt->y);
	ft_putstr(", ");
	ft_putnbr(pt->z);
	ft_putchar(')');
}
