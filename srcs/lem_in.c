/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:53:46 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/12 19:14:12 by sregnard         ###   ########.fr       */
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
		free_all(&li);
		return (SUCCESS);
}
