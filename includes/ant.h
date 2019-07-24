/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 21:00:00 by chrhuang          #+#    #+#             */
/*   Updated: 2019/07/24 10:52:07 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANT_H
# define ANT_H

# include "lem_in.h"

/*
**		ANTS
*/

typedef struct			s_ant
{
	int					id;
	bool				moved;
	t_room				*room;
	t_path				*path;
	struct s_ant		*next;
	unsigned int		flags;
}						t_ant;

typedef struct			s_list_ant
{
	t_ant				*first;
	t_ant				*current;
	t_ant				*last;
	int					size;
}						t_list_ant;

enum					e_flags_ants
{
	FLAG_ARRIVED = (1 << 0),
};

#endif
