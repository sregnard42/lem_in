/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:11 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/09 13:36:28 by chrhuang         ###   ########.fr       */
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
	if (!(li->ants = malloc(sizeof(t_ant *) * li->nb_ants + 1)))
		trigger_error(li, "Init ants : Malloc FAIL\n");
	ft_bzero(li->ants, sizeof(t_ant *) * li->nb_ants + 1);
	while (++i < li->nb_ants)
	{
		if (!(li->ants[i] = malloc(sizeof(t_ant))))
			trigger_error(li, "Init ants : Malloc FAIL\n");
		ft_bzero(li->ants[i], sizeof(t_ant));
		li->ants[i]->id = i;
	}
	return (SUCCESS);
}

void	jesaispasquoimettre(t_li *li)
{
	int			i;
	int			j;
	t_list_path	*paths;

	i = 1;
	while (li->paths_opti[i + 1])
		++i;
	paths = li->paths_opti[i];
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
		ft_printf("lead = %d\n", i);
		while (i < paths->current->capacity + j)
			li->ants[i++]->stage = paths->current->start;
		paths->current = paths->current->next;
	}
}

int	move_ant(t_li *li, t_ant **ant)
{
	(*ant)->stage = (*ant)->stage->next;
	if ((*ant)->stage->room->id == li->rooms->end->id)
	{
		(*ant)->flags |= FLAG_ARRIVED;
		ft_printf("Je suis la fourmi %d et je suis à la fin\n", (*ant)->id);
	}
	return ((*ant)->flags & FLAG_ARRIVED ? SUCCESS : FAIL);
}

void	jesaispasquoimettre_bis(t_li *li)
{
	int	nb_ant_arrived;
	int	i;
	t_list_path	*paths;

	i = 1;
	while (li->paths_opti[i + 1])
		++i;
	paths = li->paths_opti[i];
	// La je prend le dernier element de paths_opti mais il faut pas
	nb_ant_arrived = 0;
	while (nb_ant_arrived < li->nb_ants)
	{
		paths->current = paths->first;
		while (paths->current)
		{
			i = 0;
			while (paths->current->ant + i < paths->current->ant + paths->current->capacity)
			{
				if (!(li->ants[paths->current->ant + i]->flags & FLAG_ARRIVED))
				{
					
					if (move_ant(li, &li->ants[paths->current->ant + i]) == SUCCESS)
					{
						++nb_ant_arrived;
						if (li->ants[paths->current->ant + 10]->flags & FLAG_LEAD)
							++paths->current->ant;
						// Passer la fourmi a un autre path
					}
				}
//				ft_printf("i = %d\n", i);
//				ft_printf("ant->id = %d\n", paths->current);
				++i;
			}
			ft_printf("\n");
			paths->current = paths->current->next;
		}
		ft_printf("----------\n");
		//break ;
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
