/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_maxflow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:59:33 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/05 18:51:32 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	check_room(t_li *li, t_room *room, int turn)
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
			return (clear_queue(li, room));
		}
		if (child->flags & FLAG_RESERVED && li->flags & FLAG_FIRST_TRY)
		{
			room->links->current = room->links->current->next;
			continue ;
		}
		if (child->flags & FLAG_VISITED || child->weight < 1)
		{
			room->links->current = room->links->current->next;
			continue ;
		}
		child->flags |= FLAG_VISITED;
		enqueue(li, room->links->current->dst, turn + 1);
		child->parent = room;
		room->links->current = room->links->current->next;
	}
	return (FAIL);
}

int			bfs_maxflow(t_li *li, int turn)
{
	if (check_room(li, li->rooms->start, turn) == SUCCESS)
		return (SUCCESS);
	li->queue->current = li->queue->first;
	while (li->queue->current)
	{
		li->queue->current ? turn = li->queue->current->turn : 0;
		if (check_room(li, li->queue->current->room, turn) == SUCCESS)
			return (SUCCESS);
		dequeue(li);
	}
	return (FAIL);
}
