/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:27:48 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/26 13:29:28 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include "lem_in.h"

/*
**		QUEUE
*/

typedef struct			s_queue
{
	t_room				*room;
	struct s_queue		*next;
}						t_queue;

typedef struct			s_list_queue
{
	t_queue				*first;
	t_queue				*current;
	t_queue				*last;
}						t_list_queue;

#endif
