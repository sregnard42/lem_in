/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:59:33 by sregnard          #+#    #+#             */
/*   Updated: 2019/07/24 09:59:23 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**			Add room to the end of the queue
*/

static int	enqueue(t_li *li, t_room *room, int turn)
{
	t_queue	*elem;

	if (!(elem = (t_queue *)malloc(sizeof(t_queue))))
		trigger_error(li, "enqueue : error malloc\n");
	elem->room = room;
	elem->turn = turn;
	elem->next = NULL;
	if (li->queue->last)
	{
		li->queue->last->next = elem;
		li->queue->last = elem;
		return (SUCCESS);
	}
	li->queue->first = elem;
	li->queue->current = elem;
	li->queue->last = elem;
	return (SUCCESS);
}

/*
**			Eject first room from the queue
*/

static int	dequeue(t_li *li)
{
	t_queue	*queue;

	if (!li->queue->first)
		return (SUCCESS);
	queue = li->queue->first->next;
	free(li->queue->first);
	li->queue->first = queue;
	li->queue->current = queue;
	if (!queue)
		li->queue->last = queue;
	return (SUCCESS);
}

static int	check_room(t_li *li, t_room *room, int turn)
{
	t_room	*child;

	room->links->current = room->links->first;
	while (room->links->current)
	{
		child = room->links->current->dst;
		parent_of(child, room) ? room->links->current->flags |= FLAG_CLOSED : 0;
		if (room->links->current->flags & FLAG_CLOSED)
		{
			room->links->current = room->links->current->next;
			continue ;
		}
		enqueue(li, room->links->current->dst, turn + 1);
		parent_add(child, room);
		room->links->current = room->links->current->next;
	}
	return (SUCCESS);
}

int			tree(t_li *li, int turn)
{
	check_room(li, li->rooms->start, turn);
	li->queue->current = li->queue->first;
	while (li->queue->current)
	{
		li->queue->current ? turn = li->queue->current->turn : 0;
		check_room(li, li->queue->current->room, turn);
		dequeue(li);
	}
	return (SUCCESS);
}
