/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:18:32 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/19 18:06:10 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	room_add(t_room **last, t_room *new_room)
{
	if (!last || !(*last) || !new_room)
		return ;
	new_room->prev = (*last);
	(*last)->next = new_room;
	(*last) = new_room;
}

t_room	*room_new(char *name, t_point *pos)
{
	t_room	*room;

	if (!(room = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	ft_bzero(room, sizeof(t_room));
	room->name = ft_strdup(name);
	ft_ptcpy(&room->pos, pos);
	return (room);
}

void	room_free(t_room **ptr)
{
	t_room	*room;

	room = *ptr;
	ft_memdel((void **)&room->name);
	while (room->links_start)
	{
		room->links = room->links_start;
		room->links_start = room->links->next;
		link_free(&room->links);
	}
	ft_memdel((void **)ptr);
}

void	room_print(t_room *room)
{
	ft_printf("ROOM_PRINT\n");
	ft_printf("name : %s\n", room->name);
	ft_printf("pos : ");
	ft_ptprint(&room->pos);
	ft_putln();
	ft_printf("nb_links = %d\n", room->nb_links);
	ft_printf("links :\n");
	while (room->links)
	{
		link_print(room->links);
		room->links = room->links->next;
	}
	ft_printf("ants :\n");
	ft_printf("/ROOM_PRINT\n\n");
}
