/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   booking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 17:45:26 by chrhuang          #+#    #+#             */
/*   Updated: 2019/07/01 16:26:24 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		booking_turn(t_li *li, int turn) //Changer le nom si plus d'inspiration
{
	ft_printf("booking_size = %d - ", li->max_turn);
	ft_printf("turn = %d\n", turn);
	li->rooms->start->links->current = li->rooms->start->links->first;
	while (li->rooms->start->links->current)
	{
		li->rooms->start->links->current->flags = 0;
		li->rooms->start->links->current = li->rooms->start->links->current->next;
	}
	li->rooms->current = li->rooms->start;
	while (li->rooms->current)
	{
		li->rooms->current->flags = 0;
		li->rooms->current = li->rooms->current->next;
	}
	li->bookings[turn]->current = li->bookings[turn]->first;
	while (li->bookings[turn]->current)
	{
		li->bookings[turn]->current->room->flags |= FLAG_RESERVED;
		li->bookings[turn]->current = li->bookings[turn]->current->next;
	}
	return (SUCCESS);
}

void	print_booking(t_li *li)
{
	int	i;

	i = 0;
	while (++i < li->max_turn)
	{
		ft_printf("turn : [%d]\n", i);
		li->bookings[i]->current = li->bookings[i]->first;
		if (!li->bookings[i]->first)
		{
			ft_printf("Do nothing at this turn\n");
			break ;
		}
		while (li->bookings[i]->current != NULL)
		{
			ft_printf("%s ", li->bookings[i]->current->room->name);
			li->bookings[i]->current = li->bookings[i]->current->next;
		}
		ft_printf("\n");
	}
}

t_booking	*new_booking(t_room *room)
{
	t_booking	*new;

	if ((new = (t_booking *)malloc(sizeof(t_booking))) == NULL)
		return (NULL);
	ft_bzero(new, sizeof(t_booking));
	new->room = room;
	new->next = NULL;
	return (new);
}

int		add_booking(t_li *li, t_room *room, int turn)
{
	t_booking	*new;

	if (room == li->rooms->start || room == li->rooms->end)
		return (SUCCESS);
	if ((new = new_booking(room)) == NULL)
		return (ERROR);
	if (li->bookings[turn]->first == NULL)
	{
		li->bookings[turn]->first = new;
		li->bookings[turn]->current = new;
		li->bookings[turn]->last = new;
		++li->bookings[turn]->size;
	}
	li->bookings[turn]->last->next = new;
	li->bookings[turn]->last = new;
	/*rooms = li->bookings[turn]->rooms;
	if (rooms->size == 0)
	{
		rooms->start = room;
		rooms->current = room;
		rooms->end = room;
		++rooms->size;
		return (SUCCESS);
	}*/
	(void)room;
	return (SUCCESS);
}

int		booking_init(t_li *li)
{
	int	i;

	i = -1;
	li->max_turn = li->rooms->size + li->ants->size;
	if ((li->bookings = (t_list_booking **)malloc(sizeof(t_list_booking *) *
	li->max_turn)) == NULL)
		return (ERROR);
	while (++i < li->max_turn)
	{
		if ((li->bookings[i] = (t_list_booking *)malloc(sizeof(t_list_booking))) == NULL)
			return (ERROR);
		ft_bzero(li->bookings[i], sizeof(t_list_booking));
	}
	return (SUCCESS);
}
