/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   booking.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:28:54 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/30 14:18:13 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOOKING_H
# define BOOKING_H

# include "lem_in.h"

/*
**		BOOKING
*/

typedef struct			s_booking
{
	t_room				*room;
	struct s_booking	*next;
}						t_booking;

typedef struct			s_list_booking
{
	t_booking			*first;
	t_booking			*current;
	t_booking			*last;
	int					size;
}						t_list_booking;

#endif
