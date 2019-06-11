/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:53:46 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/11 18:56:52 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			main(int ac, char **av)
{
		t_point	pos;
		t_room	*room1;
		t_room	*room2;
		t_link	*link;
		t_li	li;

		ft_bzero(&li, sizeof(t_li));
		if (--ac == 0)
			trigger_error(&li, "No argument\n");
		if (parsing(ac, ++av, &li) != SUCCESS)
			return (ERROR);

/*
		// Room 1
		ft_ptset(&pos, 1, 1, 0);
		room1 = room_new("test1", pos);
		room_print(room1);

		// Room 2
		ft_ptset(&pos, 2, 2, 0);
		room2 = room_new("test2", pos);
		room_print(room2);

		// Link 1-2
		link = link_new(room1, room2);
		link_print(link);

		link_free((void **)&link, sizeof(t_link *));
		ft_putendl("Free roooooooms");
		room_free((void **)&room1, sizeof(t_room *));
		room_free((void **)&room2, sizeof(t_room *));

		// 				free
		ft_lstdel(li->ants, &ant_free);	return (SUCCESS);

		*/
		return (SUCCESS);
}
