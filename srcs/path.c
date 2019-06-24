/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 18:08:18 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/24 16:11:56 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		path_new(t_li *li, int turn)
{
	path_insert(li->ants, li->end, turn);
	while (li->room)
	{
		li->room != li->start ? li->room->flags |= FLAG_RESERVED : 0;
		path_insert(li->ants, li->room, turn);
		li->room = li->room->parent;
	}
	path_print(li->ants->path);
	return (SUCCESS);
}

int		path_init(t_li *li)
{
	int		cpt;
	int		turn;

	cpt = 0;
	turn = 0;
	li->ants = li->ants_start;
	while (cpt < li->nb_ants)
	{
		while (li->ants)
		{
			if (bfs(li, turn) == FAIL)
				break ;
			path_new(li, turn);
			room_clean(li, li->start);
			li->ants = li->ants->next;
			++cpt;
		}
		++turn;
		if (turn > 0)
			return (FAIL);
	}
	return (SUCCESS);
}

int     path_insert(t_ant *ant, t_room *room, int round)
{
	t_path	*path;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		return (FAIL);
	path->room = room;
	path->next = NULL;
	path->round = round;
	if (!ant->path_start)
	{
		ant->path_start = path;
		ant->path = path;
		ant->path_last = path;
		return (SUCCESS);
	}
	path->next = ant->path_start;
	ant->path_start = path;
	ant->path = path;
	return (SUCCESS);
}

void    path_print(t_path *path)
{
	t_path *tmp;

	tmp = path;
	while (tmp)
	{
		ft_printf("%s[%d]", tmp->room->name, tmp->round);
		tmp = tmp->next;
		tmp ? ft_putstr("->") : ft_putstr("\n");
	}
}
