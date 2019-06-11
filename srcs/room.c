/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:18:32 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/11 15:29:28 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*room_new(char *name, t_point pos)
{
		t_room	*room;

		room = (t_room *)malloc(sizeof(t_room));
		ft_bzero(room, sizeof(t_room));
		room->name = name;
		room->pos = pos;
}
