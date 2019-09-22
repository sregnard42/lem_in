/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 12:46:43 by sregnard          #+#    #+#             */
/*   Updated: 2019/09/22 16:39:25 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		link_add(t_li *li, t_room *src, t_room *dst)
{
	t_link	*link;

	if (dst == li->rooms->start || src == li->rooms->end)
		return (SUCCESS);
	li += 0;
	if (!(link = (t_link *)ft_memalloc(sizeof(t_link))))
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
	link->prev = src->links->last;
	src->links->last->next = link;
	src->links->last = link;
	return (SUCCESS);
}

int				link_new(t_li *li, t_room *a, t_room *b)
{
	if (!a)
		return (FAIL);
	if (!b)
		return (FAIL);
	if (li->links[a->id][b->id] == true)
		return (SUCCESS);
	li->links[a->id][b->id] = true;
	li->links[b->id][a->id] = true;
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
