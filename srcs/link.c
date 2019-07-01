/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 12:46:43 by sregnard          #+#    #+#             */
/*   Updated: 2019/07/01 14:59:09 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				link_clean(t_li *li, t_link *link)
{
	while (link)
	{
		link->dst != li->rooms->end ? link->flags &= ~FLAG_USED : 0;
		link = link->next;
	}
	return (SUCCESS);
}

static int		link_add(t_li *li, t_room *src, t_room *dst)
{
	t_link	*link;

	if (dst == li->rooms->start || src == li->rooms->end)
		return (SUCCESS);
	if (!(link = (t_link *)malloc(sizeof(t_link))))
		return (FAIL);
	link->dst = dst;
	link->next = NULL;
	++src->links->size;
	link->flags = 0;
	if (!src->links->first)
	{
		src->links->first = link;
		src->links->current = link;
		src->links->last = link;
		return (SUCCESS);
	}
	src->links->last->next = link;
	src->links->last = link;
	return (SUCCESS);
}

int				link_new(t_li *li, t_room *a, t_room *b)
{
	if (!a)
	{
		ft_putendl("a NULL");
		return (FAIL);
	}
	if (!b)
	{
		ft_putendl("b NULL");
		return (FAIL);
	}
	if (link_add(li, a, b) == FAIL)
		return (FAIL);
	if (link_add(li, b, a) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

void			link_print(t_link *link)
{
	ft_printf("-> %s\n", link->dst->name);
}
