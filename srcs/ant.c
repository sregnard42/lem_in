/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:11 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/11 14:24:06 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**		malloc of nb_ants + 1 because ant[0] isn't used
*/

int			ants_init(t_li *li)
{
	int	i;

	i = 0;
	if (!(li->ants = (t_ant *)malloc(sizeof(t_ant) * (li->nb_ants + 1))))
		trigger_error(li, "Init ants : Error malloc\n");
	ft_bzero(li->ants, sizeof(t_ant) * (li->nb_ants + 1));
	return (SUCCESS);
}

void	ants_set_stage(t_li *li)
{
	int			i;
	int			j;
	t_list_path	*paths;

	i = 1;
	j = 1;
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

int	ant_move(t_li *li, t_ant *ant)
{
	if (!(ant->flags & FLAG_DEPARTED) && ant->stage->room != li->rooms->end)
	{
		ant->flags |= FLAG_DEPARTED;
		ft_printf("\033[1;32m");
	}
	else
	{
		ant->stage->room == li->rooms->end ? ft_printf("\033[1;31m"):
		ft_printf("\033[1;33m");
	}
	ft_printf("L%d-%s", ant->id, ant->stage->room->name);
		ft_printf("\033[0m");
	if (ant->stage->room == li->rooms->end)
		ant->flags |= FLAG_ARRIVED;
	ant->stage = ant->stage->next;
	return (ant->flags & FLAG_ARRIVED ? 1 : 0);
}

static int	ants_move_path(t_li *li, t_list_path *paths)
{
	int	i;
	int	id;
	int	nb_arrived;

	i = 0;
	id = paths->current->ant;
	nb_arrived = 0;
	while (id + i <= li->nb_ants && li->ants[id + i].flags & FLAG_MOVING
		&& !(i > 0 && li->ants[id + i].flags & FLAG_LEAD))
	 {
		if (!(li->ants[id + i].flags & FLAG_ARRIVED))
		{
			li->flags & FLAG_SP ? ft_printf(" ") : (li->flags |= FLAG_SP);
			nb_arrived += ant_move(li, &li->ants[id + i]);
		}
		++i;
	}
	id + i <= li->nb_ants ? li->ants[id + i].flags |= FLAG_MOVING : 0;
	return (nb_arrived);
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
			nb_arrived += ants_move_path(li, paths);
			paths->current = paths->current->next;
		}
		ft_printf("\n");
	}
}
