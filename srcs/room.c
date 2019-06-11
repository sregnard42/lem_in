/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:18:32 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/11 19:18:04 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*room_new(char *name, t_point pos)
{
		t_room	*room;

		if (!(room = (t_room *)malloc(sizeof(t_room))))
				return (NULL);
		ft_bzero(room, sizeof(t_room));
		room->name = name;
		room->pos = pos;
		return (room);
}

void	room_free(void **ptr, size_t size)
{
		t_room	*room;

		room = *ptr;
		ft_printf("Freeing room : %s. Starting.\n", room->name);
		ft_lstdel(&room->links, &link_free);
		ft_lstdel(&room->ants, &ant_free);
//		ft_memdel((void **)&room->name);
		ft_bzero(*ptr, size);
		ft_memdel(ptr);
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
				ft_printf("link");
		ft_printf("ants :\n");
		while (room->ants)
				ft_printf("ant");
		ft_printf("/ROOM_PRINT\n\n");
}
