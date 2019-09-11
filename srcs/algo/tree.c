/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:59:33 by sregnard          #+#    #+#             */
/*   Updated: 2019/09/11 10:43:53 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	check_link(t_li *li, t_room *room)
{
	t_room	*child;

	child = room->links->current->dst;
	parent_of(child, room) ? room->links->current->flags |= FLAG_CLOSED : 0;
	if (room->links->current->flags & FLAG_CLOSED)
		return ;
	child->distance == 0 ? child->distance = room->distance + 1 : 0;
	if (child->distance == room->distance &&
			child != li->rooms->end && room != li->rooms->end)
		return ;
	if (!(child->flags & FLAG_QUEUED))
	{
		enqueue(li, li->queue, child);
		child->flags |= FLAG_QUEUED;
	}
	relative_add(&child->parents, room);
	relative_add(&room->childs, child);
}

static int	check_room(t_li *li, t_room *room)
{
	room->links->current = room->links->first;
	while (room->links->current)
	{
		check_link(li, room);
		room->links->current = room->links->current->next;
	}
	return (SUCCESS);
}

int			tree(t_li *li)
{
	check_room(li, li->rooms->start);
	li->queue->current = li->queue->first;
	while (li->queue->current)
	{
		check_room(li, li->queue->current->room);
		dequeue(li->queue);
	}
	return (SUCCESS);
}
