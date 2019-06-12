/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:18:32 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/12 18:21:03 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	room_add(t_room **last, t_room *new)
{
	if (!last || !(*last) || !new)
		return ;
	(*last)->next = new;
	(*last) = new;
}

t_room	*room_new(char *name, t_point *pos)
{
		t_room	*room;

		if (!(room = (t_room *)malloc(sizeof(t_room))))
				return (NULL);
		ft_bzero(room, sizeof(t_room));
		room->name = ft_strdup(name);
		ft_ptcpy(&room->pos, pos);
		room->links = NULL;
		room->ants = NULL;
		return (room);
}

void	room_free(t_room **ptr)
{
		t_room	*room;

		room = *ptr;
		ft_memdel((void **)&room->name);
		while (room->ants_start)
		{
				room->ants = room->ants_start;
				room->ants_start = room->ants->next;
				ant_free(&room->ants);
		}
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
		ft_printf("nb_ants = %d\n", room->nb_ants);
		ft_printf("links :\n");
		while (room->links)
		{
				ft_printf("%p - name = %s\n", room->links->dst, room->links->dst->name);
				room->links = room->links->next;
		}
		ft_printf("ants :\n");
		while (room->ants)
		{
				ft_printf("name = %d\n", room->ants->id);
				room->ants = room->ants->next;
		}
		ft_printf("/ROOM_PRINT\n\n");
}
