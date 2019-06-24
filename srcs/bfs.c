/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:59:33 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/24 14:34:53 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**			Add room to the end of the queue
*/

static int	enqueue(t_li *li, t_room *room)
{
	t_queue	*elem;

	if (!(elem = (t_queue *)malloc(sizeof(t_queue))))
		trigger_error(li, "enqueue : error malloc\n");
	elem->room = room;
	elem->next = NULL;
	if (li->queue_last)
	{
		li->queue_last->next = elem;
		li->queue_last = elem;
		return (SUCCESS);
	}
	li->queue_start = elem;
	li->queue = elem;
	li->queue_last = elem;
	return (SUCCESS);
}

/*
**			Eject first room from the queue
*/

static int	dequeue(t_li *li)
{
	t_queue	*queue;

	if (!li->queue_start)
		return (SUCCESS);
	queue = li->queue_start->next;
	if (li->queue_start == li->queue_last)
		li->queue_last = queue;
	free(li->queue_start);
	li->queue_start = queue;
	return (SUCCESS);
}

static int	clear_queue(t_li *li, t_room *room)
{
	while (li->queue_start)
	{
		li->queue = li->queue_start;
		li->queue_start = li->queue->next;
		free(li->queue);
	}
	li->room = room;
	return (SUCCESS);
}

static int	check_room(t_li *li, t_room *room)
{
	t_room	*child;

	dequeue(li);
	room->links = room->links_start;
	while (room->links)
	{
		child = room->links->dst;
		if (child == li->end)
			return (clear_queue(li, room));
		if (child->flags & FLAG_QUEUED)
			continue ;
		enqueue(li, room->links->dst);
		child->parent = room;
		room->links = room->links->next;
	}
	return (FAIL);
}

int			bfs(t_li *li, int turn)
{
	turn += 0;
	check_room(li, li->start);
	li->queue = li->queue_start;
	while (li->queue)
	{
		if (check_room(li, li->queue->room) == SUCCESS)
			return (SUCCESS);
		li->queue = li->queue->next;
	}
	return (FAIL);
}






