/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:40:32 by sregnard          #+#    #+#             */
/*   Updated: 2019/07/09 14:38:18 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**		Add a parent to a room
*/

int		parent_add(t_room *child, t_room *room)
{
	t_parent	*parent;

	if (!(parent = (t_parent *)malloc(sizeof(t_parent))))
		return (ERROR);
	parent->room = room;
	parent->next = NULL;
	if (!child->parents)
	{
		if (!(child->parents = (t_list_parent *)malloc(sizeof(t_list_parent))))
			return (ERROR);
		child->parents->first = parent;
		child->parents->current = parent;
		child->parents->last = parent;
	}
	else
	{
		child->parents->last->next = parent;
		child->parents->last = parent;
	}
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

int		parent_print(t_room *room, t_parent *parent)
{
	ft_printf("%s is a child of %s\n", room->name, parent->room->name);
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
