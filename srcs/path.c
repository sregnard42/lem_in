/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 18:08:18 by chrhuang          #+#    #+#             */
/*   Updated: 2019/07/31 17:53:18 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	path_new(t_li *li)
{
	li += 0;
	return (SUCCESS);
}

int			path_init(t_li *li)
{
	int	max_path;

	max_path = (li->rooms->start->nb_child > li->rooms->end->parents->size ?
	li->rooms->end->parents->size : li->rooms->start->nb_child);
	room_print_all(li->rooms->start);
	while (max_path != li->paths->size)
	{
		if (bfs_maxflow(li, 0) == FAIL)
		{
			ft_printf("BFS FAIL\n");
			room_clean(li, li->rooms->start);
			break ;
		}
		break ;
		ft_printf("BFS SUCCESS\n");
		path_new(li);
		room_clean(li, li->rooms->start);
	}
	return (SUCCESS);
}
/*
int			path_turn(t_li *li, int turn)
{
	t_stage	*path;

	path = li->ants->current->path->current;
	while (path != NULL)
	{
		path->turn = turn;
		path->room->reserv[turn++] = true;
		path = path->next;
	}
	return (SUCCESS);
}

static int	path_new(t_li *li, int turn)
{
	path_insert(li->ants->current, li->rooms->end, turn);
	while (li->rooms->current)
	{
		li->rooms->current != li->rooms->start ?
		li->rooms->current->flags |= FLAG_RESERVED : 0;
		path_insert(li->ants->current, li->rooms->current, turn);
		li->rooms->current->weight--;
		li->rooms->current = li->rooms->current->parent;
	}
	path_turn(li, turn); //Changer le nom mdr #Pas d'inspi
	path_print(li->ants->current->path->current);
	return (SUCCESS);
}

int			path_init(t_li *li)
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
			{
				room_clean(li, li->rooms->start);
				break ;
			}
			path_new(li, turn);
			room_clean(li, li->rooms->start);
			li->ants->current = li->ants->current->next;
			++cpt;
		}
		li->flags &= ~FLAG_DIRECT;
		if (++turn >= li->max_turn)
			return (FAIL);
	}
	return (SUCCESS);
}
*/
int			path_insert(t_ant *ant, t_room *room, int turn)
{
	t_stage	*path;

	if (!(path = (t_stage *)malloc(sizeof(t_stage))))
		return (FAIL);
	path->room = room;
	path->next = NULL;
	path->turn = turn;
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

void		path_print(t_stage *path)
{
	t_stage *tmp;

	tmp = path;
	while (tmp)
	{
		ft_printf("%s[%d]", tmp->room->name, tmp->turn);
		tmp = tmp->next;
		tmp ? ft_putstr("->") : ft_putstr("\n");
	}
}
