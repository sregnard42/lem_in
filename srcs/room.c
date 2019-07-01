/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:18:32 by sregnard          #+#    #+#             */
/*   Updated: 2019/07/01 14:51:06 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	room_clean(t_li *li, t_room *room)
{
	while (room)
	{
		room->flags &= ~FLAG_VISITED;
		room->flags & FLAG_RESERVED ? 0 : link_clean(li, room->links->first);
		link_clean(li, room->links->first);
		room = room->next;
	}
}

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
	if ((room->links = (t_list_link *)malloc(sizeof(t_list_link))) == NULL)
		return (NULL);
	ft_bzero(room->links, sizeof(t_list_link));
	room->name = ft_strdup(name);
	ft_ptcpy(&room->pos, pos);
	return (room);
}

void	room_print(t_room *room)
{
	ft_printf("ROOM_PRINT\n");
	ft_printf("name : %s\n", room->name);
	ft_printf("pos : ");
	ft_ptprint(&room->pos);
	ft_putln();
	ft_printf("nb_links = %d\n", room->links->size);
	ft_printf("links :\n");
	room->links->current = room->links->first;
	while (room->links->current)
	{
		link_print(room->links->current);
		room->links->current = room->links->current->next;
	}
	if (room->flags & FLAG_VISITED)
		ft_printf("visited\n");
	else
		ft_printf("not visited\n");
	ft_printf("ants :\n");
	ft_printf("/ROOM_PRINT\n\n");
}
