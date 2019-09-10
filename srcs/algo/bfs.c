/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:59:33 by sregnard          #+#    #+#             */
/*   Updated: 2019/09/10 09:55:42 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	check_room(t_li *li, t_room *room)
{
	t_room	*child;

	room->links->current = room->links->first;
	while (room->links->current)
	{
		child = room->links->current->dst;
		if (child == li->rooms->end &&
			!(room == li->rooms->start && li->flags & FLAG_DIRECT))
		{
			(room == li->rooms->start) ? li->flags |= FLAG_DIRECT : 0;
			return (SUCCESS);
		}
		if (child->flags & FLAG_VISITED)
		{
			room->links->current = room->links->current->next;
			continue ;
		}
		child->flags |= FLAG_VISITED;
		child->flags & FLAG_RESERVED ?
		enqueue(li, li->queue_res, room->links->current->dst) :
		enqueue(li, li->queue, room->links->current->dst);
		child->parent = room;
		room->links->current = room->links->current->next;
	}
	return (FAIL);
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
