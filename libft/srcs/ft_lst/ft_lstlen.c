/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 15:45:22 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/20 10:07:50 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstlen(t_list **alst)
{
	int		len;
	t_list	*elem;

	len = 0;
	if (alst && *alst)
	{
		elem = *alst;
		while (elem)
		{
			len++;
			elem = elem->next;
		}
	}
	return (len);
}
