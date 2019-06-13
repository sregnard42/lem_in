/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:12:26 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/13 15:34:19 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int search_path(t_room *room)
{
    if (!room->links)
    {
        room->flags &= ~FLAG_BUSY;
        room->links = room->links_start;
        return (room->path ? SUCCESS : FAIL);
    }
    room->flags |= FLAG_BUSY;
    /*
    if (new_path() <= path)
        path = new_path
    */
    room->links = room->links->next;
    search_path(room);
}