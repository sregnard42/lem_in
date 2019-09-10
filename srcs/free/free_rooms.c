/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 15:21:16 by chrhuang          #+#    #+#             */
/*   Updated: 2019/09/10 09:58:04 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	free_parents(t_room *room)
{
	while (room->parents && room->parents->first)
	{
		room->parents->current = room->parents->first;
		room->parents->first = room->parents->current->next;
		ft_memdel((void **)&room->parents->current);
	}
	ft_memdel((void **)&room->parents);
}

static void	free_childs(t_room *room)
{
	while (room->childs && room->childs->first)
	{
		room->childs->current = room->childs->first;
		room->childs->first = room->childs->current->next;
		ft_memdel((void **)&room->childs->current);
	}
	ft_memdel((void **)&room->childs);
}

static void	free_links(t_room *room)
{
	while (room->links && room->links->first)
	{
		room->links->current = room->links->first;
		room->links->first = room->links->current->next;
		ft_memdel((void **)&room->links->current);
	}
	ft_memdel((void **)&room->links);
}

static void	free_room(t_room **room_ptr)
{
	t_room	*room;

	if (!room_ptr || !*room_ptr)
		return ;
	room = *room_ptr;
	ft_memdel((void **)&room->name);
	free_links(room);
	free_parents(room);
	free_childs(room);
	ft_memdel((void **)room_ptr);
}

void		free_rooms(t_li *li)
{
	while (li->rooms && li->rooms->start)
	{
		li->rooms->current = li->rooms->start;
		li->rooms->start = li->rooms->current->next;
		li->rooms->current == li->start ? li->start = NULL : 0;
		li->rooms->current == li->end ? li->end = NULL : 0;
		free_room(&li->rooms->current);
	}
	ft_memdel((void **)&li->rooms);
	free_room(&li->start);
	free_room(&li->end);
}
