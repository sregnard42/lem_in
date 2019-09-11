/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:11 by sregnard          #+#    #+#             */
/*   Updated: 2019/09/11 11:17:04 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**		malloc of nb_ants
*/

int			ants_init(t_li *li)
{
	int	i;

	i = 0;
	if (!(li->ants = (t_ant *)ft_memalloc(sizeof(t_ant) * (li->nb_ants))))
		trigger_error(li, "Init ants : Error malloc\n");
	return (SUCCESS);
}

void		ants_set_stage(t_li *li)
{
	int			i;
	int			j;
	t_list_path	*paths;

	i = 0;
	paths = li->paths_opti[0];
	paths->current = paths->first;
	while (paths->current)
	{
		j = i;
		paths->current->ant = i;
		li->ants[i].flags |= FLAG_LEAD;
		li->ants[i].flags |= FLAG_MOVING;
		while (i < paths->current->capacity + j)
		{
			li->ants[i].id = i;
			li->ants[i++].stage = paths->current->start;
		}
		paths->current = paths->current->next;
	}
}

static int	ant_move(t_li *li, t_ant *ant)
{
	if (!(ant->flags & FLAG_DEPARTED) && ant->stage->room != li->rooms->end)
	{
		ant->flags |= FLAG_DEPARTED;
		li->flags & FLAG_COLOR ? ft_printf("%s", GREEN) : 0;
	}
	else if (li->flags & FLAG_COLOR)
	{
		ant->stage->room == li->rooms->end ? ft_printf("%s", RED) :
			ft_printf("%s", YELLOW);
	}
	ft_printf("L%d-%s", ant->id + 1, ant->stage->room->name);
	li->flags & FLAG_COLOR ? ft_printf("%s", RESET) : 0;
	if (ant->stage->room == li->rooms->end)
		ant->flags |= FLAG_ARRIVED;
	ant->stage = ant->stage->next;
	return (ant->flags & FLAG_ARRIVED ? 1 : 0);
}

/*
**	path->ant = id of the first ant that is still moving in this path
**	++path->ant when an ant arrives, so the next one becomes the "first ant"
*/

static int	ants_move_path(t_li *li, t_path *path)
{
	int			id;
	int			arrived;

	id = path->ant;
	arrived = 0;
	while (id < li->nb_ants && li->ants[id].flags & FLAG_MOVING
		&& !(id - path->ant > 0 && li->ants[id].flags & FLAG_LEAD))
	{
		if (!(li->ants[id].flags & FLAG_ARRIVED))
		{
			print_turn(li);
			li->flags & FLAG_SP ? ft_printf(" ") : (li->flags |= FLAG_SP);
			if (ant_move(li, &li->ants[id]))
			{
				++arrived;
				if (path->ant < li->nb_ants - 1 &&
					!(li->ants[path->ant + 1].flags & FLAG_LEAD))
					++path->ant;
			}
		}
		++id;
	}
	id < li->nb_ants && !(li->ants[id].flags & FLAG_LEAD) ?
	li->ants[id].flags |= FLAG_MOVING : 0;
	return (arrived);
}

void		ants_move(t_li *li)
{
	t_list_path	*paths;
	int			nb_arrived;

	paths = li->paths_opti[0];
	nb_arrived = 0;
	while (nb_arrived < li->nb_ants)
	{
		li->flags &= ~FLAG_SP;
		paths->current = paths->first;
		while (paths->current)
		{
			nb_arrived += ants_move_path(li, paths->current);
			paths->current = paths->current->next;
		}
		ft_printf("\n");
	}
}
