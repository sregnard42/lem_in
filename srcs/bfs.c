/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:59:33 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/05 22:12:47 by sregnard         ###   ########.fr       */
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
			return (clear_queue(li->queue));
		}
		if (child->flags & FLAG_VISITED || child->reserv[turn + 1]
				|| room->links->current->flags & FLAG_USED)
		{
			room->links->current = room->links->current->next;
			continue ;
		}
		room->links->current->flags |= FLAG_USED;
		child->flags |= FLAG_VISITED;
		enqueue(li, li->queue, room->links->current->dst, turn + 1);
		child->parent = room;
		room->links->current = room->links->current->next;
	}
	return (FAIL);
}

int			bfs(t_li *li, int turn)
{
	if (check_room(li, li->rooms->start, turn) == SUCCESS)
		return (SUCCESS);
	li->queue->current = li->queue->first;
	while (li->queue->current)
	{
		li->rooms->current = li->queue->current->room;
		li->queue->current ? turn = li->queue->current->turn : 0;
		if (check_room(li, li->queue->current->room, turn) == SUCCESS)
			return (SUCCESS);
		dequeue(li->queue);
	}
	return (FAIL);
}
