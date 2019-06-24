/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:53:46 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/24 14:47:05 by sregnard         ###   ########.fr       */
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

int			free_all(t_li *li)
{
	while (li->start)
	{
		li->room = li->start;
		li->start = li->room->next;
		room_free(&li->room);
	}
	while (li->ants_start)
	{
		li->ants = li->ants_start;
		li->ants_start = li->ants->next;
		ant_free(&li->ants);
	}
	return (SUCCESS);
}

int			main()
{
	t_li	li;

	ft_bzero(&li, sizeof(t_li));
	if (parsing(&li) != SUCCESS)
		return (ERROR);
	ft_putstr(li.buf);
	ant_print_all(&li);
	/*************
	  ALGO START
	 *************/
	ft_printf("ALGO START\n");

	path_init(&li);

	ft_printf("ALGO END\n");
	/*************
	  ALGO END
	 *************/
	ant_print_all(&li);
	free_all(&li);
	return (SUCCESS);
}
