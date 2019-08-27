/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 19:37:16 by chrhuang          #+#    #+#             */
/*   Updated: 2019/08/25 15:04:52 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

/*
**	current	: first room in the list
**	last	: last room in the list
**	start	: starting room, placed at the beginning when parsing done
**	end		: ending room, placed at the end when parsing done
*/

static int	is_room(t_li *li, char **line)
{
	if (!line || !*line)
		trigger_error(li, "Bad line\n");
	ft_strequ(START, *line) ? li->flags |= FLAG_START : 0;
	ft_strequ(END, *line) ? li->flags |= FLAG_END : 0;
	if (*line[0] == '#')
		return (FAIL);
	if (*line[0] == 'L')
		trigger_error(li, "Invalid name #room\n");
	if (ft_nb_str_tab(line) != 3)
		trigger_error(li, "Invalid nb arguments #room\n");
	if (!ft_isinteger(line[1]) || !ft_isinteger(line[2]))
		trigger_error(li, "Not integer #room\n");
	return (SUCCESS);
}

static int	add_room(t_li *li, t_room **rooms, char **tab, t_room **last)
{
	t_room	*new;
	t_point	pos;

	ft_ptset(&pos, ft_atoi(tab[1]), ft_atoi(tab[2]), 0);
	if ((new = room_new(li, tab[0], &pos)) == NULL)
		return (ERROR);
	if (li->flags & FLAG_START || li->flags & FLAG_END)
	{
		if (li->flags & FLAG_START)
		{
			if (li->rooms->start)
				trigger_error(li, "Multi start\n");
			li->rooms->start = new;
		}
		else
		{
			if (li->rooms->end)
				trigger_error(li, "Multi end\n");
			li->rooms->end = new;
		}
		li->flags & FLAG_START ?
			(li->flags &= ~FLAG_START) : (li->flags &= ~FLAG_END);
		return (SUCCESS);
	}
	*rooms == NULL ? *rooms = new : room_add(last, new);
	*rooms == new ? *last = *rooms : 0;
	return (SUCCESS);
}

int			place_start_end(t_li *li, t_room **last)
{
	if (!li->rooms->start || !li->rooms->end)
		trigger_error(li, "No start or end #room\n");
	li->flags &= ~FLAG_ROOM;
	li->flags |= FLAG_LINK;
	(!li->rooms->current) ? li->rooms->current = li->rooms->start : 0;
	(!(*last)) ? *last = li->rooms->current : 0;
	if (li->rooms->current != li->rooms->start)
	{
		li->rooms->start->next = li->rooms->current;
		li->rooms->current->prev = li->rooms->start;
		li->rooms->current = li->rooms->start;
	}
	room_add(last, li->rooms->end);
	(*last)->id = li->rooms->size - 1;
	new_matrice(li, li->rooms->size);
	return (SUCCESS);
}

int			get_room(t_li *li, char *line, t_room **last)
{
	t_room	*rooms;
	char	**tab;

	tab = ft_strsplit(line, '-');
	if (is_link(li, tab) == SUCCESS)
	{
		place_start_end(li, last);
		ft_free_tab(&tab);
		return (FAIL);
	}
	ft_free_tab(&tab);
	rooms = li->rooms->current;
	tab = ft_strsplit(line, ' ');
	if (is_room(li, tab) == FAIL || add_room(li, &rooms, tab, last) == ERROR)
	{
		ft_free_tab(&tab);
		return (FAIL);
	}
	li->rooms->current = rooms;
	//++li->rooms->size;
	ft_free_tab(&tab);
	return (SUCCESS);
}
