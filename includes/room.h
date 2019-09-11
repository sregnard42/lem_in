/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 20:55:45 by chrhuang          #+#    #+#             */
/*   Updated: 2019/09/11 09:53:46 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOM_H
# define ROOM_H

# include "lem_in.h"

/*
**		ROOMS
*/

typedef struct				s_room
{
	char					*name;
	int						id;
	int						distance;
	t_point					pos;
	struct s_list_link		*links;
	struct s_list_relative	*parents;
	struct s_list_relative	*childs;
	struct s_room			*parent;
	struct s_room			*child;
	struct s_path			*path;
	struct s_room			*next;
	struct s_room			*prev;
	unsigned int			flags;
}							t_room;

typedef struct				s_list_room
{
	t_room					*start;
	t_room					*current;
	t_room					*end;
	int						size;
}							t_list_room;

enum						e_flags_room
{
	FLAG_VISITED = (1 << 0),
	FLAG_RESERVED = (1 << 1),
	FLAG_QUEUED = (1 << 2),
};

#endif
