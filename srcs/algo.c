/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:12:26 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/19 13:31:07 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	valid_path(t_li *li, t_ant *ant, t_room *room)
{
	if (room->links->dst == li->end)
		return (SUCCESS);
	if (!room->links)
	{
		room->flags &= ~FLAG_VISITED;
		room->links = room->links_start;
		return (FAIL);
	}
	
	room->flags |= FLAG_VISITED;

	if (valid_path(li, ant, room) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int shortest_path(t_li *li, t_ant *ant, t_room *room)
{
	if (!room->links)
	{
		room->flags &= ~FLAG_VISITED;
		room->links = room->links_start;
		return (ant->path ? SUCCESS : FAIL);
	}
	room->flags |= FLAG_VISITED;
	/*
	   if (new_path() <= path)
	   path = new_path
	 */
	room->links = room->links->next;
	search_path(li, ant, room);
	return (SUCCESS);
}

int init_paths(t_li *li)
{
	li->ants = li->ants_start;
	while (li->ants)
	{
		if (search_path(li, li->ants, li->start) == FAIL)
			return (FAIL);
		li->ants = li->ants->next;
	}
	return (SUCCESS);
}