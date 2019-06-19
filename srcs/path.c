/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 18:08:18 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/19 18:10:06 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int     add_to_path(t_ant *ant, t_room *room, int round)
{
    t_path	*path;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		return (FAIL);
	path->room = room;
	path->next = NULL;
	path->round = round;
	if (!ant->path_start)
	{
        ant->path_start = path;
		ant->path = path;
		ant->path_last = path;
		return (SUCCESS);
	}
	path->next = ant->path_start;
    ant->path_start = path;
    ant->path = path;
	return (SUCCESS);
}

void    path_print(t_path *path)
{
    t_path *tmp;

    tmp = path;
    while (tmp)
    {
        ft_printf("%s[%d]", tmp->room->name, tmp->round);
        tmp = tmp->next;
        tmp ? ft_putstr("->") : ft_putstr("\n");
    }
}