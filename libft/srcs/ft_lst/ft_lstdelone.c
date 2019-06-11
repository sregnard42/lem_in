/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 14:37:51 by sregnard          #+#    #+#             */
/*   Updated: 2018/12/03 09:10:18 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void **, size_t))
{
	t_list	*elem;
	t_list	*next;
	t_list	*prev;

	elem = *alst;
	if (!elem)
		return ;
	prev = elem->prev;
	next = elem->next;
	if (prev && next)
	{
		prev->next = next;
		next->prev = prev;
	}
	else if (prev)
		prev->next = next;
	else if (next)
		next->prev = prev;
	del((void **)&(elem->content), elem->content_size);
	ft_memdel((void **)alst);
}
