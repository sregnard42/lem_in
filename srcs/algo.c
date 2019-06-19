/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:12:26 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/19 17:36:51 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*int	valid_path(t_li *li, t_ant *ant, t_room *room)
{
	if (room->links->dst == li->end)
		return (SUCCESS);
	if (!room->links->dst)
	{
		room->flags &= ~FLAG_VISITED;
		room->links = room->links_start;
		return (FAIL);
	}
	// ???
	room->flags |= FLAG_VISITED;
	if (valid_path(li, ant, room) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int shortest_path(t_li *li, t_ant *ant, t_room *room)
{
	if (!room->links)
	{
		room->flags &= ~FLAG_VISITED;
		room->links = room->links_start;
		return (ant->path ? SUCCESS : FAIL);
	}
	room->flags |= FLAG_VISITED;
	
	//   if (new_path() <= path)
	//  path = new_path
	 
	room->links = room->links->next;
	shortest_path(li, ant, room);
	return (SUCCESS);
}*/

static int	first_path(t_li *li, t_ant *ant, t_room *room)
{
	t_link	*tmp;

	if (room->flags & FLAG_VISITED)
		return (FAIL);
	ft_printf("room-=>name = %s\n", room->name);
	ant += 0;
	if (room == li->end)
	{
		add_to_path(ant, room);
		ft_printf("Je suis a la fin Youhou \n");
		return (SUCCESS);
	}
	tmp = room->links_start;
	while (tmp != NULL)
	{
		room->flags |= FLAG_VISITED;
		if (first_path(li, ant, tmp->dst) == SUCCESS)
			add_to_path(ant, room);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int init_paths(t_li *li)
{
	li->ants = li->ants_start;
	while (li->ants)
	{
		if (first_path(li, li->ants, li->start) == FAIL)
			return (FAIL);
		li->ants = li->ants->next;
	}
	path_print(li->ants_start->path_start);
	return (SUCCESS);
}