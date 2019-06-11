/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 14:49:08 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/29 13:19:03 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void **, size_t))
{
	t_list	*elem;
	t_list	*next;

	elem = *alst;
	while (elem)
	{
		next = elem->next;
		ft_lstdelone(&elem, del);
		elem = next;
	}
	*alst = NULL;
}
