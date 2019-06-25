/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 18:08:18 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/25 20:36:50 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		path_new(t_li *li, int turn)
{
	path_insert(li->ants->current, li->rooms->end, turn);
	while (li->rooms->current)
	{
		li->rooms->current != li->rooms->start ?
		li->rooms->current->flags |= FLAG_RESERVED : 0;
		path_insert(li->ants->current, li->rooms->current, turn);
		li->rooms->current = li->rooms->current->parent;
	}
	path_print(li->ants->current->path->current);
	return (SUCCESS);
}

int		path_init(t_li *li)
{
	int		cpt;
	int		turn;

	cpt = 0;
	turn = 0;
	li->ants->current = li->ants->first;
	while (cpt < li->ants->size)
	{
		while (li->ants->current)
		{
			if (bfs(li, turn) == FAIL)
				break ;
			path_new(li, turn);
			room_clean(li, li->rooms->start);
			li->ants->current = li->ants->current->next;
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
	if (!ant->path->start)
	{
		ant->path->start = path;
		ant->path->current = path;
		ant->path->end = path;
		return (SUCCESS);
	}
	path->next = ant->path->start;
	ant->path->start = path;
	ant->path->current = path;
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
