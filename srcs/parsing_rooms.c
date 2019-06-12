/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 19:37:16 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/12 13:53:58 by chrhuang         ###   ########.fr       */
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

static int	add_room(t_list **rooms, char **tab)
{
		t_list	*new;
		t_room	*tmp;
		t_point	pos;

		ft_printf("nb1 = %d\nnb2 = %d\n", ft_atoi(tab[1]), ft_atoi(tab[2]));
		ft_ptset(&pos, ft_atoi(tab[1]), ft_atoi(tab[2]), 0);
		ft_ptprint(&pos);
		ft_putln();
		tmp = room_new(tab[0], &pos);
		new = ft_lstnew(tmp, sizeof(tmp));
		*rooms == NULL ? *rooms = new : ft_lstadd(rooms, new);
		return (SUCCESS);
}

int	get_rooms(t_li *li, char *line)
{
	t_list	*rooms;
	char	**tab;

	rooms = NULL;
	tab = ft_strsplit(line, ' ');
	if (is_room(li, tab) == FAIL)
	{
		ft_printf("no rooms = %s\n", line);
		return (FAIL);
	}
	ft_printf("is a room = %s\n", line);
	add_room(&rooms, tab);
	return (SUCCESS);
}
