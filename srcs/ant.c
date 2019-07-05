/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:11 by sregnard          #+#    #+#             */
/*   Updated: 2019/07/05 13:43:44 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	ants_add(t_li *li, t_ant *ant)
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
}

int			ants_init(t_li *li, int nb_ants)
{
	t_ant	*ant;
	int		i;

	i = 0;
	li->ants->size = nb_ants;
	while (++i <= nb_ants)
	{
		if (!(ant = (t_ant *)malloc(sizeof(t_ant))))
			return (FAIL);
		ft_bzero(ant, sizeof(t_ant));
		ant->id = i;
		ant->room = li->rooms->start;
		if ((ant->path = (t_list_path *)malloc(sizeof(t_list_path))) == NULL)
			trigger_error(li, "ants_init malloc NULL\n");
		ft_bzero(ant->path, sizeof(t_list_path));
		ants_add(li, ant);
	}
	return (SUCCESS);
}

int			ant_move(t_ant *ant, t_room *dst)
{
	dst->flags |= FLAG_RESERVED;
	ant->room->flags &= ~FLAG_RESERVED;
	ant->room = dst;
	ant->moved = 1;
	return (SUCCESS);
}

void		ant_print(t_ant *ant)
{
	ft_printf("L%d-%s ", ant->id, ant->path->current->room->name);
//	ant->moved ? 0 : ft_printf("(X) ");
//	ant->path->current ? path_print(ant->path->current) : ft_printf("nah\n");
}

void		ant_print_all(t_li *li)
{
	li->ants->current = li->ants->first;
	while (li->ants->current)
	{
		li->ants->current->moved ? ant_print(li->ants->current) : 0;
		//ant_print(li->ants->current);
		li->ants->current = li->ants->current->next;
	}
	li->ants->current = li->ants->first;
	ft_putln();
}
