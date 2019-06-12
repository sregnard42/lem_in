/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 19:37:16 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/12 16:18:25 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

static int	is_room(t_li *li, char **line)
{
		if (!line)
				return (FAIL);
		ft_strequ(START, *line) ? li->flags |= FLAG_START : 0;
		ft_strequ(END, *line) ? li->flags |= FLAG_END : 0;
		if (*line[0] == '#')
				return (FAIL);
		if (ft_nb_str_tab(line) != 3)
				return (FAIL);
		if (!ft_isinteger(line[1]) || !ft_isinteger(line[2]))
				return (FAIL);
		return (SUCCESS);
}

static int	add_room(t_li *li, t_room **rooms, char **tab, t_room **last)
{
		t_room	*new;
		t_point	pos;

		ft_ptset(&pos, ft_atoi(tab[1]), ft_atoi(tab[2]), 0);
		new = room_new(tab[0], &pos);
		if (li->flags & FLAG_START || li->flags & FLAG_END)
		{
				li->flags & FLAG_START ?
						(li->start = new) : (li->end = new);
				li->flags & FLAG_START ?
						(li->flags &= ~FLAG_START) : (li->flags &= ~FLAG_END);
				return (SUCCESS);
		}
		*rooms == NULL ? *rooms = new : room_add(last, new);
		*rooms == new ? *last = *rooms : 0;
		return (SUCCESS);
}

int	get_room(t_li *li, char *line, t_room **last)
{
		t_room	*rooms;
		char	**tab;

		tab = ft_strsplit(line, '-');
		if (is_link(tab) == SUCCESS)
		{
				li->flags &= ~FLAG_ROOM;
				li->flags |= FLAG_LINK;
				li->start->next = li->room;
				li->room = li->start;
				room_add(last, li->end);
				return (FAIL);
		}
		rooms = li->room;
		tab = ft_strsplit(line, ' ');
		if (is_room(li, tab) == FAIL)
				return (FAIL);
		add_room(li, &rooms, tab, last);
		li->room = rooms;
		return (SUCCESS);
}
