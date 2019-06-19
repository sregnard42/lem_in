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

int search_path(t_ant *ant, t_room *room)
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
	search_path(ant, room);
	return (SUCCESS);
}
