/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   booking.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:28:54 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/26 13:29:21 by sregnard         ###   ########.fr       */
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
	int					turn;
	t_list_room			*rooms;
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
