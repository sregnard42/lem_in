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

static int	first_path(t_li *li, t_ant *ant, t_room *room, int round)
{
	t_link	*tmp;

	if (room->flags & FLAG_VISITED)
		return (FAIL);
	ant += 0;
	if (room == li->end)
	{
		add_to_path(ant, room, round);
		ft_printf("Je suis a la fin Youhou \n");
		return (SUCCESS);
	}
	tmp = room->links_start;
	while (tmp != NULL)
	{
		room->flags |= FLAG_VISITED;
		if (first_path(li, ant, tmp->dst, round + 1) == SUCCESS)
			add_to_path(ant, room, round);
		tmp = tmp->next;
	}
	if (ant->path_start == NULL)
	{
		ft_printf("Je suis dans le if\n");
		return (FAIL);
	}
	return (SUCCESS);
}

void	tmp_reset_rooms_flags(t_li *li)
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
	int		cpt;
	int		round;

	cpt = 0;
	round = 0;
	li->ants = li->ants_start;
	while (cpt < li->nb_ants)
	{
		while (li->ants)
		{
			if (first_path(li, li->ants, li->start, round) == FAIL)
				break;
			cpt++;
			li->ants = li->ants->next;
		}
		tmp_reset_rooms_flags(li);
		round++;
	}
	path_print(li->ants_start->path_start);
	path_print(li->ants_start->next->path_start);
	path_print(li->ants_start->next->next->path_start);
	return (SUCCESS);
}