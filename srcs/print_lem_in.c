/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lem_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:00:28 by chrhuang          #+#    #+#             */
/*   Updated: 2019/07/05 13:50:23 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	current_to_first(t_li *li)
{
	li->ants->current = li->ants->first;
	while (li->ants->current != NULL)
	{
		li->ants->current->path->current = li->ants->current->path->start;
		li->ants->current = li->ants->current->next;
	}
	li->ants->current = li->ants->first;
}

void	print_lem_in(t_li *li)
{
	int		turn;
	t_ant	*ant;
	int		i;

	turn = -1;
	current_to_first(li);
	while (++turn < li->max_turn)
	{
		ant = li->ants->current;
		i = 0;
		while (ant != NULL)
		{
			if (ant->flags & FLAG_ARRIVED)
			{
				++i;
				if (i == li->ants->size)
					return ;
				ant = ant->next;
				continue ;
			}
			if (ant->path->current->turn == turn)
			{
				ant->path->current = ant->path->current->next;
				if (ant->path->current != NULL)
					ant_print(ant);
				ant->path->current == NULL ? ant->flags |= FLAG_ARRIVED : 0;
			}
			ant = ant->next;
		}
		ft_putln();
	}
}