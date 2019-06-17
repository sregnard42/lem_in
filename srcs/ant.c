/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:11 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/17 17:42:27 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ants_init(t_li *li, int nb_ants)
{
	t_ant	*ant;
	int		i;

	i = 0;
	li->nb_ants = nb_ants;
	while (++i <= nb_ants)
	{
		if (!(ant = (t_ant *)malloc(sizeof(t_ant))))
				return (FAIL);
		ft_bzero(ant, sizeof(t_ant));
		ant->id = i;
		ant->room = li->start;
		if (i == 1)
		{
				li->ants_start = ant;
				li->ants = ant;
				li->ants_last = ant;
		}
		else
		{
				li->ants_last->next = ant;
				li->ants_last = ant;
		}
	}
	return (SUCCESS);
}

void	ant_free(t_ant **ptr)
{
		ft_memdel((void **)ptr);
}

void	ant_print(t_ant	*ant)
{
		ft_printf("L%d-%s ", ant->id, ant->room->name);
		ant->moved ? 0 : ft_printf("(X) ");
}

void	ant_print_all(t_li *li)
{
		while (li->ants)
		{
				li->ants->moved ? ant_print(li->ants) : 0;
				li->ants = li->ants->next;
		}
}
