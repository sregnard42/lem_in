/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:59:33 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/26 13:38:39 by sregnard         ###   ########.fr       */
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
		ft_printf("%s", queue->room->name);
		queue = queue->next;
		queue ? ft_printf(", ") : ft_printf("\n");
	}
	return (SUCCESS);
}

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

static int	check_room(t_li *li, t_room *room)
{
	t_room	*child;

	dequeue(li);
	room->links->current = room->links->first;
	while (room->links->current)
	{
		child = room->links->current->dst;
		if (room->links->current->flags & FLAG_USED
				|| child->flags & FLAG_VISITED || child->flags & FLAG_RESERVED)
		{
			room->links->current = room->links->current->next;
			continue ;
		}
		room->links->current->flags |= FLAG_USED;
		child->flags |= FLAG_VISITED;
		if (child == li->rooms->end)
			return (clear_queue(li, room));
		enqueue(li, room->links->current->dst);
		child->parent = room;
		room->links->current = room->links->current->next;
	}
	return (FAIL);
}

int			bfs(t_li *li, int turn)
{
	turn += 0;
	ant_print(li->ants->current);
	ft_putln();
	if (check_room(li, li->rooms->start) == SUCCESS)
		return (SUCCESS);
	li->queue->current = li->queue->first;
	queue_print(li->queue->current);
	while (li->queue->current)
	{
		if (check_room(li, li->queue->current->room) == SUCCESS)
			return (SUCCESS);
		queue_print(li->queue->current);
	}
	return (FAIL);
}
