/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   booking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 17:45:26 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/30 12:30:08 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// On doit creer une list chaine avec les rooms et etc

int	booking_init(t_li *li)
{
	unsigned int	i;

	i = -1;
	li->booking_size = li->rooms->size + li->ants->size;
	if ((li->bookings = (t_booking *)malloc(sizeof(t_booking) *
	li->booking_size)) == NULL)
		return (ERROR);
	while (++i < li->booking_size)
	{
		ft_bzero(li->bookings[i].rooms, sizeof(t_list_room));
		ft_bzero(li->bookings[i].next, sizeof(t_booking));
	}
	return (SUCCESS);
}
