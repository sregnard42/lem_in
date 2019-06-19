/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:12:26 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/19 18:13:15 by chrhuang         ###   ########.fr       */
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

static int first_path(t_li *li, t_ant *ant, t_room *room, int round)
{
	t_link *tmp;

	if (room->flags & FLAG_VISITED && room != li->start)
		return (FAIL);
	if (room == li->end)
	{
		add_to_path(ant, room, round);
		ft_printf("Path found\n");
		return (SUCCESS);
	}
	room->flags |= FLAG_VISITED;
	tmp = room->links_start;
	while (tmp != NULL)
	{
		if (first_path(li, ant, tmp->dst, round + 1) == SUCCESS)
		{
			add_to_path(ant, room, round);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	if (ant->path_start == NULL)
	{
		ft_printf("No path\n");
		return (FAIL);
	}
	return (SUCCESS);
}

void tmp_reset_rooms_flags(t_li *li)
{
	li->room = li->start;
	while (li->room != NULL)
	{
		li->room->flags = 0;
		li->room = li->room->next;
	}
}

int init_paths(t_li *li)
{
	int cpt;
	int round;

	cpt = 0;
	round = 0;
	li->ants = li->ants_start;
	while (cpt < li->nb_ants)
	{
		while (li->ants)
		{
			if (first_path(li, li->ants, li->start, round) == FAIL)
				break;
			else
				path_print(li->ants->path_start);
			cpt++;
			li->ants = li->ants->next;
		}
		ft_printf("Rooooommmssssss\n");
		tmp_reset_rooms_flags(li);
		round++;
	}
	li->ants = li->ants_start;
	/*
	while (li->ants)
	{
		path_print(li->ants->path);
		li->ants = li->ants->next;
	}
	*/
	return (SUCCESS);
}