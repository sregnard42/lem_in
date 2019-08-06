/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:59:33 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/06 13:20:34 by sregnard         ###   ########.fr       */
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
		parent_of(child, room) ? room->links->current->flags |= FLAG_CLOSED : 0;
		if (room->links->current->flags & FLAG_CLOSED)
		{
			room->links->current = room->links->current->next;
			continue ;
		}
		child->distance == 0 ? child->distance = room->distance + 1 : 0;
		if (child->distance == room->distance &&
			child != li->rooms->end && room != li->rooms->end)
		{
			++room->nb_child;
			++room->weight;
			room->links->current = room->links->current->next;
			continue ;
		}
		if (!(child->flags & FLAG_QUEUED))
		{
			enqueue(li, li->queue, child, 0);
			child->flags |= FLAG_QUEUED;
		}
		parent_add(child, room);
		room->links->current = room->links->current->next;
	}
	return (SUCCESS);
}

int			tree(t_li *li)
{
	ft_printf("tree : BEGIN\n");
	check_room(li, li->rooms->start);
	li->queue->current = li->queue->first;
	while (li->queue->current)
	{
		queue_print(li->queue);
		check_room(li, li->queue->current->room);
		dequeue(li->queue);
	}
	ft_printf("tree : END\n");
	return (SUCCESS);
}
