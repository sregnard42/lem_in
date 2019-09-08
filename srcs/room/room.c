/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:18:32 by sregnard          #+#    #+#             */
/*   Updated: 2019/09/08 13:55:38 by chrhuang         ###   ########.fr       */
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
		room = room->next;
	}
}

void	room_add(t_li *li, t_room *new_room)
{
	if (!li->rooms->start)
	{
		li->rooms->start = new_room;
		li->rooms->current = new_room;
		li->rooms->end = new_room;
		return ;
	}
	new_room->prev = li->rooms->end;
	li->rooms->end->next = new_room;
	li->rooms->end = new_room;
}

t_room	*room_new(t_li *li, char *name, t_point *pos)
{
	t_room				*room;
	static unsigned int	id = 1;

	if (!(room = (t_room *)ft_memalloc(sizeof(t_room))))
		return (NULL);
	if ((room->links = (t_list_link *)ft_memalloc(sizeof(t_list_link))) == NULL)
		return (NULL);
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
	room->links->current = room->links->first;
	while (room->links->current)
	{
		link_print(room->links->current);
		room->links->current = room->links->current->next;
	}
	if (room->parents)
	{
		ft_printf("\033[1;33mParents [%d] : ", room->parents->size);
		room->parents->current = room->parents->first;
		while (room->parents->current)
		{
			ft_printf("%s", room->parents->current->room->name);
			room->parents->current = room->parents->current->next;
			room->parents->current ? ft_printf(", ") : ft_printf("\033[0m\n");
		}
	}
	if (room->childs)
	{
		ft_printf("\033[1;35mChilds [%d] : ", room->childs->size);
		room->childs->current = room->childs->first;
		while (room->childs->current)
		{
			ft_printf("%s", room->childs->current->room->name);
			room->childs->current = room->childs->current->next;
			room->childs->current ? ft_printf(", ") : ft_printf("\033[0m\n");
		}
	}
	ft_printf("\033[1;34m/ROOM_PRINT\033[0m\n\n");
}

void	room_print_all(t_li *li)
{
	li->rooms->current = li->rooms->start;
	while (li->rooms->current)
	{
		room_print(li->rooms->current);
		li->rooms->current = li->rooms->current->next;
	}
}
