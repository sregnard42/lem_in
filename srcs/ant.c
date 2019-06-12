/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:11 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/12 13:52:09 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ants_init(t_room *r, int nb_ants)
{
	t_ant	*ant;
	int		i;

	i = 0;
	while (++i <= nb_ants)
	{
		ant->id = i;
		if (!(ant = (t_ant *)malloc(sizeof(t_ant))))
				return (FAIL);
		ant->id = i;
		ant->moved = 0;
		if (i == 1)
		{
				r->ants_start = ant;
				r->ants = ant;
				r->ants_last = ant;
		}
		else
		{
				r->ants_last->next = ant;
				r->ants_last = ant;
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
		ft_printf("#%-5d ", ant->id);
		ant->moved ? ft_printf("moving\n") : ft_printf("waiting\n");
}
