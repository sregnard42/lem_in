/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:11 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/09 16:40:22 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*static int	ants_add(t_li *li, t_ant *ant)
{
	if (ant->id == 1)
	{
		li->ants->first = ant;
		li->ants->current = ant;
		li->ants->last = ant;
	}
	else
	{
		li->ants->last->next = ant;
		li->ants->last = ant;
	}
	return (SUCCESS);
}*/

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
	// La je prend le dernier element de paths_opti mais il faut pas
	path_print_all(paths);
	paths->current = paths->first;
	i = 1;
	j = 1;
	while (paths->current)
	{
//		ft_printf("i = %d\n", i);
		j = i;
		paths->current->ant = i;
		li->ants[i]->flags |= FLAG_LEAD;
		li->ants[i]->flags |= FLAG_MOVING;
		ft_printf("lead = %d\n", i);
		while (i < paths->current->capacity + j)
		{
			li->ants[i++]->stage = paths->current->start;
		}
		paths->current = paths->current->next;
	}
}

int	ant_move(t_li *li, t_ant **ant)
{
	if (!((*ant)->flags & FLAG_DEPARTED) && (*ant)->stage->room != li->rooms->end)
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
	{
		(*ant)->flags |= FLAG_ARRIVED;
		//ft_printf("Je suis la fourmi %d et je suis à la fin\n", (*ant)->id);
	}
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
	// La je prend le dernier element de paths_opti mais il faut pas
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

/*
int			ant_move(t_ant *ant, t_room *dst)
{
	dst->flags |= FLAG_RESERVED;
	ant->room->flags &= ~FLAG_RESERVED;
	ant->room = dst;
	ant->moved = 1;
	return (SUCCESS);
}

void		ant_print(t_ant *ant, t_room *end)
{
	char	*color;

	color = ant->path->current->room == end ? "1;32" : "1;33";
	ft_printf("\033[%sm", color);
	ft_printf("L%d-%s", ant->id, ant->path->current->room->name);
	ft_printf("\033[0m");
}

void		ant_print_all(t_li *li)
{
	li->ants->current = li->ants->first;
	while (li->ants->current)
	{
		li->ants->current->moved ? ant_print(li->ants->current,
				li->rooms->end) : 0;
		li->ants->current = li->ants->current->next;
	}
	li->ants->current = li->ants->first;
	ft_putln();
}*/
