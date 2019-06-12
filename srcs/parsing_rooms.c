/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 19:37:16 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/12 14:50:57 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

static int	is_room(t_li *li, char **line)
{
		if (!line)
				return (FAIL);
		ft_strequ(START, *line) ? li->flags |= FLAG_START : 0;
		//li->flags & FLAG_START; Condition pour check
		ft_strequ(END, *line) ? li->flags |= FLAG_END : 0;
		if (*line[0] == '#')
				return (FAIL);
		if (ft_nb_str_tab(line) != 3)
				return (FAIL);
		if (!ft_isinteger(line[1]) || !ft_isinteger(line[2]))
				return (FAIL);
		return (SUCCESS);
}

static int	add_room(t_li *li, t_room **rooms, char **tab, t_room *last)
{
	t_room	*new;
	t_point	pos;

	ft_ptset(&pos, ft_atoi(tab[1]), ft_atoi(tab[2]), 0);
	new = room_new(tab[0], &pos);
	if (li->flags & FLAG_START || li->flags & FLAG_END)
	{
		li->flags & FLAG_START ?
		(li->start = new) : (last = new);
		li->flags & FLAG_START ?
		(li->flags &= ~FLAG_START) : (li->flags &= ~FLAG_END);
		return (SUCCESS);
	}
	*rooms == NULL ? *rooms = new : room_add(&(li->end), new);
	*rooms == new ? li->end = *rooms : 0;
	return (SUCCESS);
}

int	get_rooms(t_li *li, char *line, t_room *last)
{
	t_room	*rooms;
	char	**tab;

	rooms = li->room;
	tab = ft_strsplit(line, ' ');
	if (is_room(li, tab) == FAIL)
	{
		//ft_printf("%s - not room\n", line);
		return (FAIL);
	}
	//ft_printf("%s - room\n", line);
	add_room(li, &rooms, tab, last);
	li->room = rooms;
	return (SUCCESS);
}
