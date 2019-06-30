/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   booking.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:28:54 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/30 11:56:31 by chrhuang         ###   ########.fr       */
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
	t_list_room			*rooms;
	struct s_booking	*next;
}						t_booking;

#endif
