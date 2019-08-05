/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:18:32 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/05 23:43:40 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	room_clean(t_li *li)
{
	t_room	*room;

	room = li->rooms->start;
	while (room)
	{
		room->flags &= ~FLAG_VISITED;
//		room->flags & FLAG_RESERVED ? 0 : link_clean(li, room->links->first);
//		link_clean(li, room->links->first);
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

t_room	*room_new(t_li *li, char *name, t_point *pos)
{
	t_room				*room;
	static unsigned int	id = 1;

	if (!(room = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	ft_bzero(room, sizeof(t_room));
	if ((room->links = (t_list_link *)malloc(sizeof(t_list_link))) == NULL)
		return (NULL);
	ft_bzero(room->links, sizeof(t_list_link));
	room->name = ft_strdup(name);
	li->rooms->size++;
	ft_ptcpy(&room->pos, pos);
	if (!(li->flags & FLAG_START || li->flags & FLAG_END))
		room->id = id++;
	return (room);
}

void	room_print(t_room *room)
{
	ft_printf("\n\033[1;34mROOM_PRINT : %s\033[0m\n", room->name);
	ft_printf("Name : %s, ", room->name);
	ft_printf("ID = %d, ", room->id);
	ft_printf("Pos : ");
	ft_ptprint(&room->pos);
	ft_putstr("\n");
	ft_printf("Weight = %d, ", room->weight);
	ft_printf("Distance = %d\n", room->distance);
	room->links->current = room->links->first;
	while (room->links->current)
	{
		link_print(room->links->current);
		room->links->current = room->links->current->next;
	}
	if (!(room->parents))
	{
		ft_printf("\033[1;34m/ROOM_PRINT\033[0m\n\n");
		return ;
	}
	ft_printf("\033[1;33mParents : ");
	room->parents->current = room->parents->first;
	while (room->parents->current)
	{
		ft_printf("%s", room->parents->current->room->name);
		room->parents->current = room->parents->current->next;
		room->parents->current ? ft_printf(", ") : ft_printf("\033[0m\n");
	}
	ft_printf("\033[1;34m/ROOM_PRINT\033[0m\n\n");
}

void	room_print_all(t_room *room)
{
	while (room)
	{
		room_print(room);
		room = room->next;
	}
}
