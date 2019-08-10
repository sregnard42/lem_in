/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:27:48 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/10 14:10:31 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include "lem_in.h"

/*
**		QUEUE
*/

typedef struct			s_queue_e
{
	t_room				*room;
	struct s_queue_e	*next;
}						t_queue_e;

typedef struct			s_queue
{
	t_queue_e			*first;
	t_queue_e			*current;
	t_queue_e			*last;
	int					size;
}						t_queue;

#endif
