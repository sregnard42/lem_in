/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 20:35:55 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/25 20:54:56 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	path_free(t_li *li)
{
	t_ant	*ant;

	ant = li->ants->current;
	while (ant->path->start)
	{
		ant->path->current = ant->path->start;
		ant->path->start = ant->path->current->next;
		free(ant->path->current);
	}
	free(ant->path);
}

void			link_free(t_li *li)
{
	t_room	*room;

	room = li->rooms->current;
	while (room->links && room->links->first)
	{
		room->links->current = room->links->first;
		room->links->first = room->links->current->next;
		free(room->links->current);
	}
	free(room->links);
}

void	ant_free(t_li *li)
{
	while (li->ants && li->ants->first)
	{
		li->ants->current = li->ants->first;
		li->ants->first = li->ants->current->next;
		path_free(li);
		free(li->ants->current);
	}
}

void	room_free(t_li *li)
{
	while (li->rooms && li->rooms->start)
	{
		li->rooms->current = li->rooms->start;
		li->rooms->start = li->rooms->current->next;
		ft_memdel((void **)&li->rooms->current->name);
		link_free(li);
		free(li->rooms->current);
	}
}

int			free_all(t_li *li)
{
	if (!li)
		return (SUCCESS);
	ant_free(li);
	room_free(li);
	free(li->rooms);
	free(li->ants);
	free(li->queue);
	free(li->bookings);
	return (SUCCESS);
}
