/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:59:33 by sregnard          #+#    #+#             */
/*   Updated: 2019/09/22 16:22:35 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	check_link(t_li *li, t_room *room)
{
	t_room	*child;

	child = room->links->current->dst;
	if (child == li->rooms->end &&
			!(room == li->rooms->start && li->flags & FLAG_DIRECT))
	{
		(room == li->rooms->start) ? li->flags |= FLAG_DIRECT : 0;
		return (SUCCESS);
	}
	if (child->flags & FLAG_VISITED)
		return (FAILURE);
	child->flags |= FLAG_VISITED;
	child->flags & FLAG_RESERVED ?
		enqueue(li, li->queue_res, room->links->current->dst) :
		enqueue(li, li->queue, room->links->current->dst);
	child->parent = room;
	return (FAILURE);
}

static int	check_room(t_li *li, t_room *room)
{
	room->links->current = li->flags & FLAG_REVERSE ?
		room->links->last : room->links->first;
	while (room->links->current)
	{
		if (check_link(li, room) == SUCCESS)
			return (SUCCESS);
		room->links->current = li->flags & FLAG_REVERSE ?
		room->links->current->prev : room->links->current->next;
	}
	return (FAILURE);
}

int			bfs(t_li *li)
{
	t_queue		*queue;

	if (check_room(li, li->rooms->start) == SUCCESS)
		return (SUCCESS);
	li->queue->current = li->queue->first;
	while (li->queue->current || li->queue_res->current)
	{
		queue = li->queue->current ? li->queue : li->queue_res;
		li->rooms->current = queue->current->room;
		if (check_room(li, li->rooms->current) == SUCCESS)
		{
			clear_queue(li->queue);
			clear_queue(li->queue_res);
			return (SUCCESS);
		}
		dequeue(queue);
	}
	return (FAILURE);
}
