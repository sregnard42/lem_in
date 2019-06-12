/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 19:37:16 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/12 13:03:57 by chrhuang         ###   ########.fr       */
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

static int	add_room(t_list **rooms, char **line)
{
		t_list	*new;
		t_room	*tmp;
		t_point	pos;

		ft_printf("nb1 = %d\nnb2 = %d\n", ft_atoi(line[1]), ft_atoi(line[2]));
		ft_ptset(&pos, ft_atoi(line[1]), ft_atoi(line[2]), 0);
		ft_ptprint(&pos);
		ft_putln();
		tmp = room_new(line[0], &pos);
		new = ft_lstnew(tmp, sizeof(tmp));
		*rooms == NULL ? *rooms = new : ft_lstadd(rooms, new);
		return (SUCCESS);
}

int	get_rooms(t_li *li, char **tab)
{
		t_list	*rooms;
		char	**line;

		rooms = NULL;
		while (*tab)
		{
				while (*tab && is_room(li, line = ft_strsplit(*tab, ' ')) == FAIL)
				{
						ft_printf("no rooms = %s\n", *tab);
						++tab;
				}
				if (!(*tab))
						break;
				ft_printf("is a room = %s\n", *tab);
				add_room(&rooms, line);
				++tab;
		}
		t_room *room;
		while (rooms)
		{
				room = rooms->content;  
				room_print(room);
				ft_putendl("nani");
				rooms = rooms->next;
		}
		return (SUCCESS);
}
