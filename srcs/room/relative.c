/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:40:32 by sregnard          #+#    #+#             */
/*   Updated: 2019/09/10 10:16:15 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**		Add a relative to a room's list of parents/childs
*/

int		relative_add(t_list_relative **list, t_room *room)
{
	t_relative	*relative;

	if (!(relative = (t_relative *)ft_memalloc(sizeof(t_relative))))
		return (ERROR);
	relative->room = room;
	relative->next = NULL;
	if (!(*list))
	{
		if (!((*list) = (t_list_relative *)
		ft_memalloc(sizeof(t_list_relative))))
			return (ERROR);
		(*list)->first = relative;
		(*list)->current = relative;
		(*list)->last = relative;
	}
	else
	{
		(*list)->last->next = relative;
		(*list)->last = relative;
	}
	++(*list)->size;
	return (SUCCESS);
}

/*
**		Return SUCCESS if room is a parent of child
*/

int		parent_of(t_room *room, t_room *child)
{
	if (!child->parents)
		return (FAILURE);
	child->parents->current = child->parents->first;
	while (child->parents->current)
	{
		if (child->parents->current->room == room)
			return (SUCCESS);
		child->parents->current = child->parents->current->next;
	}
	return (FAILURE);
}

int		parent_print(t_room *room, t_relative *relative)
{
	ft_printf("%s is a child of %s\n", room->name, relative->room->name);
	return (SUCCESS);
}

int		parent_print_all(t_room *room)
{
	if (!room->parents)
		return (SUCCESS);
	room->parents->current = room->parents->first;
	while (room->parents->current)
	{
		parent_print(room, room->parents->current);
		room->parents->current = room->parents->current->next;
	}
	return (SUCCESS);
}
