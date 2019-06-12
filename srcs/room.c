/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:18:32 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/12 16:38:51 by sregnard         ###   ########.fr       */
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
		room->name = name;
		ft_ptcpy(&room->pos, pos);
		room->links = NULL;
		room->ants = NULL;
		return (room);
}

void	room_free(t_room **ptr)
{
		t_room	*room;

		room = *ptr;
		ft_printf("Freeing room : %s. Starting.\n", room->name);
//		ft_lstdel(&room->links, &link_free);
//		ft_lstdel(&room->ants, &ant_free);
		ft_memdel((void **)ptr);
		ft_printf("Freeing room. Done.\n");
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
