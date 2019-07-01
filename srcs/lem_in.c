/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:53:46 by sregnard          #+#    #+#             */
/*   Updated: 2019/07/01 16:35:28 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			li_buffer(t_li *li, const char *s, size_t len)
{
	size_t	i;

	i = 0;
	if (li->index + len >= PF_BUFF_SIZE)
	{
		write(1, li->buf, li->index);
		ft_bzero(li->buf, PF_BUFF_SIZE);
		li->index = 0;
	}
	while (i < len && i < LI_BUFF_SIZE)
		li->buf[li->index++] = *(s + i++);
	if (i < len)
		li_buffer(li, s + i, len - i);
	return (SUCCESS);
}

static int	init_li(t_li *li)
{
	ft_bzero(li, sizeof(t_li));
	li->rooms = (t_list_room *)malloc(sizeof(t_list_room));
	li->ants = (t_list_ant *)malloc(sizeof(t_list_ant));
	li->queue = (t_list_queue *)malloc(sizeof(t_list_queue));
	ft_bzero(li->rooms, sizeof(t_list_room));
	ft_bzero(li->ants, sizeof(t_list_ant));
	ft_bzero(li->queue, sizeof(t_list_queue));
	if (!li->rooms || !li->ants || !li->queue)
		trigger_error(li, "init_li malloc fail\n");
	return (SUCCESS);
}

static int	tab_reserv(t_li *li)
{
	li->max_turn = li->rooms->size + li->ants->size;
	li->rooms->current = li->rooms->start;
	while (li->rooms->current)
	{
		if ((li->rooms->current->reserv =
			malloc(sizeof(bool) * li->max_turn)) == NULL)
			return (ERROR);
		ft_bzero(li->rooms->current->reserv, sizeof(bool) * li->max_turn);
		li->rooms->current = li->rooms->current->next;
	}
	return (SUCCESS);
}

int			main(void)
{
	t_li	li;

	init_li(&li);
	if (parsing(&li) != SUCCESS)
		return (ERROR);
	ft_putstr(li.buf);
	ant_print_all(&li);
	/*************
	  ALGO START
	*************/
	ft_printf("ALGO START\n");
	//booking_init(&li);
	tab_reserv(&li);
	path_init(&li);
	//print_booking(&li);
	ft_printf("ALGO END\n");
	/*************
	  ALGO END
	*************/
	ant_print_all(&li);
	ft_printf("nb_rooms = %d\n", li.rooms->size);
	free_all(&li);
	return (SUCCESS);
}
