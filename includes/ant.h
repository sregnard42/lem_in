/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 21:00:00 by chrhuang          #+#    #+#             */
/*   Updated: 2019/08/09 15:16:40 by chrhuang         ###   ########.fr       */
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
	struct s_stage		*stage;
	unsigned int		flags;
}						t_ant;

enum					e_flags_ants
{
	FLAG_ARRIVED = (1 << 0),
	FLAG_MOVING = (1 << 1),
	FLAG_LEAD = (1 << 2),
	FLAG_DEPARTED = (1 << 3),
};

#endif
