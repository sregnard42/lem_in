/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 18:08:18 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/24 14:17:42 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		create_path(t_li *li, int turn)
{
	path_insert(li->ants, li->end, turn);
	path_insert(li->ants, li->room, turn);
	li->room = li->room->parent;
	while (li->room)
	{
		path_insert(li->ants, li->room, turn);
		li->room = li->room->parent;
	}
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
			create_path(li, turn);
			++cpt;
		}
		++turn;
		if (turn > 1)
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
