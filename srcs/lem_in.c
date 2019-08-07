/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:53:46 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/07 13:18:36 by chrhuang         ###   ########.fr       */
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
	li->queue = (t_queue *)malloc(sizeof(t_queue));
	li->queue_res = (t_queue *)malloc(sizeof(t_queue));
	li->paths = (t_list_path *)malloc(sizeof(t_list_path));
	ft_bzero(li->rooms, sizeof(t_list_room));
	ft_bzero(li->ants, sizeof(t_list_ant));
	ft_bzero(li->queue, sizeof(t_queue));
	ft_bzero(li->queue_res, sizeof(t_queue));
	ft_bzero(li->paths, sizeof(t_list_path));
	if (!li->rooms || !li->ants || !li->queue || !li->queue_res || !li->paths)
		trigger_error(li, "init_li malloc fail\n");
	return (SUCCESS);
}
/*
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
*/
int			main(void)
{
	t_li	li;

	init_li(&li);
	if (parsing(&li) != SUCCESS)
		return (ERROR);
	/*************
	  ALGO START
	*************/
	tree(&li);
	shortest_path_init(&li);
	path_init(&li);
	ft_printf("\033[1;36m\nAll paths :\n\033[0m");
	path_print_all(li.paths);
	li.first_path ? ft_printf("\033[1;36m\nShortest path :\n\033[0m") : 0;
	li.first_path ? path_print(li.first_path) : 0;
	print_shortest_paths(&li);
	/*************
	  ALGO END
	*************/
//	print_lem_in(&li);
	free_all(&li);
	return (SUCCESS);
}
