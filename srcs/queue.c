/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:46:42 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/05 18:51:07 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	queue_print(t_queue *queue)
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

int	enqueue(t_li *li, t_room *room, int turn)
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

int	dequeue(t_li *li)
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

int	clear_queue(t_li *li, t_room *room)
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
