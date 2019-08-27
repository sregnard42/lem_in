/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:53:46 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/25 15:10:07 by chrhuang         ###   ########.fr       */
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
	li->queue = (t_queue *)malloc(sizeof(t_queue));
	li->queue_res = (t_queue *)malloc(sizeof(t_queue));
	li->paths = (t_list_path *)malloc(sizeof(t_list_path));
	li->paths_all = (t_list_path *)malloc(sizeof(t_list_path));
	ft_bzero(li->rooms, sizeof(t_list_room));
	ft_bzero(li->queue, sizeof(t_queue));
	ft_bzero(li->queue_res, sizeof(t_queue));
	ft_bzero(li->paths, sizeof(t_list_path));
	ft_bzero(li->paths_all, sizeof(t_list_path));
	if (!li->rooms || !li->queue || !li->queue_res ||
		!li->paths || !li->paths_all)
		trigger_error(li, "init_li malloc fail\n");
	return (SUCCESS);
}

static int	repartition_lists(t_li *li, t_list_path** lists)
{
	int			i;

	i = 0;
	while (lists[++i])
		if (repartition(li, lists[i]) == FAILURE)
			trigger_error(li, "Repartition : FAILURE\n");
		else
			if (!lists[0] || lists[0]->turns > lists[i]->turns)
				lists[0] = lists[i];
	return (SUCCESS);
}

int			main(void)
{
	t_li	li;

	init_li(&li);
	if (parsing(&li) != SUCCESS)
		return (ERROR);
	ft_putstr(li.buf);
	ants_init(&li);
	tree(&li);
	paths_opti_init(&li);
	path_init(&li);
	repartition(&li, li.paths);
	repartition_lists(&li, li.paths_opti);
	ants_set_stage(&li);
	ants_move(&li);
	free_all(&li);
	return (SUCCESS);
}
