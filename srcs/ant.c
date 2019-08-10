/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:11 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/10 17:18:11 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ants_init(t_li *li)
{
	int	i;

	i = 0;
	if (!(li->ants = (t_ant **)malloc(sizeof(t_ant *) * (li->nb_ants + 2))))
		trigger_error(li, "Init ants : Malloc FAIL\n");
	ft_bzero(li->ants, sizeof(t_ant *) * (li->nb_ants + 2));
	while (++i < li->nb_ants + 1)
	{
		if (!(li->ants[i] = (t_ant *)malloc(sizeof(t_ant))))
			trigger_error(li, "Init ants : Malloc FAIL\n");
		ft_bzero(li->ants[i], sizeof(t_ant));
		li->ants[i]->id = i;
	}
	return (SUCCESS);
}

void	ants_set_stage(t_li *li)
{
	int			i;
	int			j;
	t_list_path	*paths;

	paths = li->paths_opti[0];
	paths->current = paths->first;
	i = 1;
	j = 1;
	while (paths->current)
	{
		j = i;
		paths->current->ant = i;
		li->ants[i]->flags |= FLAG_LEAD;
		li->ants[i]->flags |= FLAG_MOVING;
		while (i < paths->current->capacity + j)
			li->ants[i++]->stage = paths->current->start;
		paths->current = paths->current->next;
	}
}

int	ant_move(t_li *li, t_ant **ant)
{
	if (!((*ant)->flags & FLAG_DEPARTED) &&
	(*ant)->stage->room != li->rooms->end)
	{
		(*ant)->flags |= FLAG_DEPARTED;
		ft_printf("\033[1;32m");
	}
	else
	{
		(*ant)->stage->room == li->rooms->end ? ft_printf("\033[1;31m"):
		ft_printf("\033[1;33m");
	}
	ft_printf("L%d-%s", (*ant)->id, (*ant)->stage->room->name);
		ft_printf("\033[0m");
	if ((*ant)->stage->room == li->rooms->end)
		(*ant)->flags |= FLAG_ARRIVED;
	(*ant)->stage = (*ant)->stage->next;
	return ((*ant)->flags & FLAG_ARRIVED ? SUCCESS : FAIL);
}

void	ants_move_path(t_li *li, int *i, t_list_path *paths, int *nb_arrived)
{
	*i = 0;
	while (*i + paths->current->ant <= li->nb_ants &&
	li->ants[paths->current->ant + *i]->flags & FLAG_MOVING)
    {
    	if (*i > 0 && li->ants[paths->current->ant + *i]->flags & FLAG_LEAD)
			break ;
		if (!(li->ants[paths->current->ant + *i]->flags & FLAG_ARRIVED))
		{
			li->flags & FLAG_SP ? ft_printf(" ") : (li->flags |= FLAG_SP);
			if (ant_move(li, &li->ants[paths->current->ant + *i]) == SUCCESS)
			{
				++(*nb_arrived);
	    		if (li->ants[paths->current->ant + 1])
					if (li->ants[paths->current->ant + 1]->flags & FLAG_LEAD)
		  				++paths->current->ant;
	    		}
			}
		++(*i);
	}
}

void	ants_move(t_li *li)
{
	t_list_path	*paths;
	int			nb_ant_arrived;
	int			i;

	paths = li->paths_opti[0];
	nb_ant_arrived = 0;
	while (nb_ant_arrived < li->nb_ants)
	{
		li->flags &= ~FLAG_SP;
		paths->current = paths->first;
		while (paths->current)
		{
			ants_move_path(li, &i, paths, &nb_ant_arrived);
			if (li->ants[paths->current->ant + i])
				li->ants[paths->current->ant + i]->flags |= FLAG_MOVING;
			paths->current = paths->current->next;
		}
		ft_printf("\n");
	}
}
