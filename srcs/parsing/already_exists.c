/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   already_exists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 10:10:30 by chrhuang          #+#    #+#             */
/*   Updated: 2019/09/10 10:12:51 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	already_exists(t_li *li, char *name, t_point *pos)
{
	t_room	*room;

	room = li->start ? li->start : NULL;
	if (room && (ft_strequ(room->name, name) || ft_ptcmp(&room->pos, pos)))
		return (SUCCESS);
	room = li->end ? li->end : NULL;
	if (room && (ft_strequ(room->name, name) || ft_ptcmp(&room->pos, pos)))
		return (SUCCESS);
	room = li->rooms->start;
	while (room)
	{
		if (ft_strequ(room->name, name) || ft_ptcmp(&room->pos, pos))
			return (SUCCESS);
		room = room->next;
	}
	return (FAILURE);
}
