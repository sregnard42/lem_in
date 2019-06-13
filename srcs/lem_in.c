/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:53:46 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/13 16:23:12 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			free_all(t_li *li)
{
		while (li->start)
		{
				li->room = li->start;
				li->start = li->room->next;
				room_free(&li->room);
		}
		return (SUCCESS);
}

int			main()
{
		t_li	li;

		ft_bzero(&li, sizeof(t_li));
		if (parsing(&li) != SUCCESS)
			return (ERROR);
		/*******
		  ALGO
		  *****/
		move_ant(li.start, li.end);
		move_ant(li.start, li.end);
		//ft_putendl("START");
		//room_print(li.start);
		//ft_putendl("END");
		//room_print(li.end);
		ft_printf("MAIN\n");
		for (t_room *tmp = li.end; tmp != NULL; tmp = tmp->prev)
			ft_printf("prev = %p - name = %s\n", tmp->prev, tmp->name);
		free_all(&li);
		return (SUCCESS);
}
