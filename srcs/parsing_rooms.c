/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 19:37:16 by chrhuang          #+#    #+#             */
/*   Updated: 2019/09/04 16:39:00 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

static int	already_exists(t_li *li, char *name, t_point *pos)
{
	t_room	*room;

	room = li->start ? li->start : NULL;
	if (room && (ft_strequ(room->name, name) || ft_ptcmp(&room->pos, pos)))
			return (SUCCESS);
	room = li->end ? li->end : NULL;
	if (room && (ft_strequ(room->name, name) || ft_ptcmp(&room->pos, pos)))
			return (SUCCESS);
	room = li->rooms->start;
	while (room)
	{
		if (ft_strequ(room->name, name) || ft_ptcmp(&room->pos, pos))
			return (SUCCESS);
		room = room->next;
	}
	return (FAILURE);
}

/*
**	current	: first room in the list
**	last	: last room in the list
**	start	: starting room, placed at the beginning when parsing done
**	end		: ending room, placed at the end when parsing done
*/

static int	is_room(t_li *li)
{
	if (!li->line_split || !*li->line_split)
		trigger_error(li, "Bad line | is_room\n");
	if (!ft_strncmp("##", *li->line_split, 2)
		&& (li->flags & FLAG_START || li->flags & FLAG_END))
			trigger_error(li, "command after ##start or ##end.\n");
	ft_strequ(START, *li->line_split) ? li->flags |= FLAG_START : 0;
	ft_strequ(END, *li->line_split) ? li->flags |= FLAG_END : 0;
	if (*li->line_split[0] == '#')
		return (FAIL);
	if (*li->line_split[0] == 'L')
		trigger_error(li, "Invalid name #room\n");
	if (ft_nb_str_tab(li->line_split) != 3)
		trigger_error(li, "Invalid nb arguments #room\n");
	if (!ft_isinteger(li->line_split[1]) || !ft_isinteger(li->line_split[2]))
		trigger_error(li, "Not integer #room\n");
	return (SUCCESS);
}

static int	add_room(t_li *li)
{
	t_room	*new;
	t_point	pos;
	char	**tab;

	tab = li->line_split;
	ft_ptset(&pos, ft_atoi(tab[1]), ft_atoi(tab[2]), 0);
	if (already_exists(li, tab[0], &pos))
		trigger_error(li, "room name or pos already taken.\n");
	if ((new = room_new(li, tab[0], &pos)) == NULL)
		return (ERROR);
	if (li->flags & FLAG_START || li->flags & FLAG_END)
	{
		if (li->flags & FLAG_START)
		{
			if (li->start)
				trigger_error(li, "Multi start\n");
			li->start = new;
			li->flags &= ~FLAG_START;
		}
		else
		{
			if (li->end)
				trigger_error(li, "Multi end\n");
			li->end = new;
			li->flags &= ~FLAG_END;
		}
		return (SUCCESS);
	}
	room_add(li, new);
	return (SUCCESS);
}

int			place_start_end(t_li *li)
{
	if (!li->start || !li->end)
		trigger_error(li, "No start or end #room\n");
	li->flags &= ~FLAG_ROOM;
	li->flags |= FLAG_LINK;
	if (!li->rooms->start)
	{
		room_add(li, li->start);
		room_add(li, li->end);
	}
	else
	{
		li->start->next = li->rooms->start;
		li->rooms->start->prev = li->start;
		li->rooms->start = li->start;
		room_add(li, li->end);
	}
	li->end->id = li->rooms->size - 1;
	new_matrice(li, li->rooms->size);
	return (SUCCESS);
}

int			get_room(t_li *li)
{
	t_room	*rooms;

	li->line_split = ft_strsplit(li->line, '-');
	if (is_link(li) == SUCCESS)
	{
		place_start_end(li);
		ft_free_tab(&li->line_split);
		return (FAIL);
	}
	ft_free_tab(&li->line_split);
	rooms = li->rooms->current;
	li->line_split = ft_strsplit(li->line, ' ');
	if (is_room(li) == FAIL || add_room(li) == ERROR)
	{
		ft_free_tab(&li->line_split);
		return (FAIL);
	}
	ft_free_tab(&li->line_split);
	return (SUCCESS);
}
