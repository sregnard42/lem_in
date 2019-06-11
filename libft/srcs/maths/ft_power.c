/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 08:31:17 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/14 08:44:40 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_power(int n, unsigned int pow)
{
	int res;

	if (pow == 0)
		return (1);
	if (n == 0 || n == 1)
		return (n);
	res = n;
	while (pow-- > 1)
		res *= n;
	return (res);
}
