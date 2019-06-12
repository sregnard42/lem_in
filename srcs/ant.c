/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:11 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/12 13:36:32 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ant		ants_init(t_room *r, int nb_ants)
{
	t_ant	*ant;
	int		i;

	i = 0;
	while (++i <= nb_ants)
	{
		ant.id = i;
		if (!(ant = (t_ant *)malloc(sizeof(t_ant))))
				return (FAILURE);
		ant->id = i;
		ant->moved = 0;
		if (i == 1)
		{
				r->ant_start = ant;
				r->ant = ant;
				r->ant_last = ant;
		}
		else
				r->ant_last->next = ant;
	}
	return (SUCCESS);
}

/*/void	ant_free(t_ant **ptr)
{
		ft_printf("ant #%d freed\n", ((t_ant *)(*ptr))->id);
		//ft_bzero(*ptr, size);
		ft_memdel(ptr);
}

void	ant_print(t_ant	*ant)
{
		ft_printf("#%-3d ", ant->id);
		ant->moved ? ft_printf("moving\n") : ft_printf("waiting\n");
}
*/
