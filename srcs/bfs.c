/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:59:33 by sregnard          #+#    #+#             */
/*   Updated: 2019/07/05 12:31:19 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//TMP
static int	queue_print(t_queue *queue)
{
	if (!queue)
		ft_printf("Empty queue\n");
	while (queue)
	{
		ft_printf("%s [%d]", queue->room->name, queue->turn);
		queue = queue->next;
		queue ? ft_printf(", ") : ft_printf("\n");
	}
	return (SUCCESS);
}

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

static int	clear_queue(t_li *li, t_room *room)
{
	while (li->queue->first)
	{
		li->queue->current = li->queue->first;
		li->queue->first = li->queue->current->next;
		free(li->queue->current);
	}
	li->queue->first = NULL;
	li->queue->current = NULL;
	li->queue->last = NULL;
	li->rooms->current = room;
	return (SUCCESS);
}

static int	check_room(t_li *li, t_room *room, int turn)
{
	t_room	*child;

	li->queue->current ? turn = li->queue->current->turn : 0;
	dequeue(li);
	room->links->current = room->links->first;
	while (room->links->current)
	{
		child = room->links->current->dst;
		if (child == li->rooms->end && 
			!(room == li->rooms->start && li->flags & FLAG_DIRECT))
		{
			if (room == li->rooms->start)
				li->flags |= FLAG_DIRECT;
			return (clear_queue(li, room));
		}
		if (child->flags & FLAG_VISITED || child->reserv[turn + 1]
				|| room->links->current->flags & FLAG_USED)
		{
			room->links->current = room->links->current->next;
			continue ;
		}
		room->links->current->flags |= FLAG_USED;
		child->flags |= FLAG_VISITED;
		enqueue(li, room->links->current->dst, turn + 1);
		child->parent = room;
		room->links->current = room->links->current->next;
	}
	return (FAIL);
}

int			bfs(t_li *li, int turn)
{
	ant_print(li->ants->current);
	ft_putln();
	if (check_room(li, li->rooms->start, turn) == SUCCESS)
		return (SUCCESS);
	li->queue->current = li->queue->first;
	queue_print(li->queue->current);
	while (li->queue->current)
	{
		if (check_room(li, li->queue->current->room, turn) == SUCCESS)
			return (SUCCESS);
		queue_print(li->queue->current);
	}
	return (FAIL);
}
