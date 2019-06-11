/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:05:45 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/29 08:10:15 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	t_list	*elem;

	if (alst && *alst && new)
	{
		elem = *alst;
		while (elem->next)
		{
			elem = elem->next;
		}
		new->prev = elem;
		elem->next = new;
	}
}
