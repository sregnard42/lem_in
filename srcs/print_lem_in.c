/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lem_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:00:28 by chrhuang          #+#    #+#             */
/*   Updated: 2019/07/31 15:49:57 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	current_to_first(t_li *li)
{
	li->ants->current = li->ants->first;
	while (li->ants->current != NULL)
	{
		li->ants->current->path->current = li->ants->current->path->start;
		li->ants->current = li->ants->current->next;
	}
	li->ants->current = li->ants->first;
}

static int	check_is_arrived(t_ant **ant)
{
	if ((*ant)->flags & FLAG_ARRIVED)
	{
		(*ant) = (*ant)->next;
		return (SUCCESS);
	}
	return (FAIL);
}

static void	check_ant_turn(t_li *li, t_ant **ant, int *moved, int *i)
{
	(*ant)->path->current = (*ant)->path->current->next;
	if ((*ant)->path->current != NULL)
	{
		(*moved)++ != 0 ? ft_putstr(" ") : 0;
		ant_print(*ant, li->rooms->end);
	}
	if (!(*ant)->path->current)
	{
		(*ant)->flags |= FLAG_ARRIVED;
		++(*i);
	}
}

void		print_lem_in(t_li *li)
{
	int		turn;
	t_ant	*ant;
	int		i;
	int		moved;

	turn = -1;
	i = 0;
	current_to_first(li);
	while (++turn < li->max_turn && i < li->ants->size)
	{
		ant = li->ants->current;
		moved = 0;
		turn != 0 ? ft_putln() : 0;
		while (ant != NULL)
		{
			if (check_is_arrived(&ant) == SUCCESS)
				continue ;
			if (ant->path->current->turn == turn)
				check_ant_turn(li, &ant, &moved, &i);
			ant = ant->next;
		}
	}
}
