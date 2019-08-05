/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:46:42 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/05 22:50:00 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	queue_print(t_queue *queue)
{
	t_queue_e	*elem;

	elem = queue->first;
	if (!elem)
		ft_printf("Empty queue\n");
	while (elem)
	{
		ft_printf("%4s", elem->room->name);
		elem = elem->next;
		elem ? 0 : ft_printf("\n");
	}
	return (SUCCESS);
}

/*
**			Add room to the end of the queue
*/

int	enqueue(t_li *li, t_queue *queue, t_room *room, int turn)
{
	t_queue_e	*elem;

	if (!(elem = (t_queue_e *)malloc(sizeof(t_queue_e))))
		trigger_error(li, "enqueue : error malloc\n");
	elem->room = room;
	elem->turn = turn;
	elem->next = NULL;
	if (queue->last)
	{
		queue->last->next = elem;
		queue->last = elem;
		return (SUCCESS);
	}
	queue->first = elem;
	queue->current = elem;
	queue->last = elem;
	return (SUCCESS);
}

/*
**			Eject first room from the queue
*/

int	dequeue(t_queue *queue)
{
	t_queue_e	*elem;

	if (!queue->first)
		return (SUCCESS);
	elem = queue->first->next;
	free(queue->first);
	queue->first = elem;
	queue->current = elem;
	if (!elem)
		queue->last = elem;
	return (SUCCESS);
}

int	clear_queue(t_queue *queue)
{
	while (queue->first)
	{
		queue->current = queue->first;
		queue->first = queue->current->next;
		free(queue->current);
	}
	ft_bzero(queue, sizeof(t_queue));
	return (SUCCESS);
}
