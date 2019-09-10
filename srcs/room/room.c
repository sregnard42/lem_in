/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:18:32 by sregnard          #+#    #+#             */
/*   Updated: 2019/09/10 11:10:47 by chrhuang         ###   ########.fr       */
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
