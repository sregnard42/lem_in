/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lem_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:00:28 by chrhuang          #+#    #+#             */
/*   Updated: 2019/07/09 15:11:31 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	current_to_first(t_li *li)
{
	li->ants->current = li->ants->first;
	while (li->ants->current != NULL)
	{
		li->ants->current->path->current = li->ants->current->path->start;
		li->ants->current = li->ants->current->next;
	}
	li->ants->current = li->ants->first;
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
			if (ant->flags & FLAG_ARRIVED)
			{
				ant = ant->next;
				continue ;
			}
			if (ant->path->current->turn == turn)
			{
				ant->path->current = ant->path->current->next;
				if (ant->path->current != NULL)
				{
					moved++ != 0 ? ft_putstr(" ") : 0;
					ant_print(ant);
				}
				if (!ant->path->current && ++i)
					ant->flags |= FLAG_ARRIVED;
			}
			ant = ant->next;
		}
	}
}
