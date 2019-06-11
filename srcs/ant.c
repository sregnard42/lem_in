/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:11 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/11 19:28:15 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*ants_init(int nb_ants)
{
	t_list	*ants;
	t_list	*elem;
	t_ant	ant;
	int		i;

	ant.moved = 0;
	i = 1;
	while (i <= nb_ants)
	{
			ant.id = i;
			if (!(elem = ft_lstnew(&ant, sizeof(t_ant))))
					return (NULL);
			if (i++ == 1)
					ants = elem;
			else
					ft_lstadd(&ants, elem);
//			ft_printf("ant #%d created\n", ant.id);
//			ant_print(&ant);
	}
	return (ants);
}

void	ant_free(void **ptr, size_t size)
{
		ft_printf("ant #%d freed\n", ((t_ant *)(*ptr))->id);
		ft_bzero(*ptr, size);
		ft_memdel(ptr);
}

void	ant_print(t_ant	*ant)
{
		ft_printf("#%-3d ", ant->id);
		ant->moved ? ft_printf("moving\n") : ft_printf("waiting\n");
}
