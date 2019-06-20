/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:53:46 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/20 09:48:29 by chrhuang         ###   ########.fr       */
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
	while (li.ants)
	{
		ant_print(li.ants);
		li.ants = li.ants->next;
	}
	li.ants = li.ants_start;
	ft_putln();
	init_paths(&li);
	/*******
	  ALGO
	 *****/
	//move_ant(li.ants_start, li.end);
	ft_printf("After Algo\n");
	li.ants = li.ants_start;
	while (li.ants)
	{
		ant_print(li.ants);
		li.ants = li.ants->next;
	}
	ft_putln();
//	free_all(&li);
	return (SUCCESS);
}
