/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:53:46 by sregnard          #+#    #+#             */
/*   Updated: 2019/09/22 16:54:27 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			li_buffer(t_li *li, const char *s, size_t len)
{
	size_t	i;

	i = 0;
	if (li->index + len >= LI_BUFF_SIZE)
	{
		write(1, li->buf, li->index);
		ft_bzero(li->buf, LI_BUFF_SIZE);
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
	li->rooms = ft_memalloc(sizeof(t_list_room));
	li->queue = ft_memalloc(sizeof(t_queue));
	li->queue_res = ft_memalloc(sizeof(t_queue));
	li->paths = ft_memalloc(sizeof(t_list_path));
	li->paths_all = ft_memalloc(sizeof(t_list_path));
	if (!li->rooms || !li->queue || !li->queue_res ||
		!li->paths || !li->paths_all)
		trigger_error(li, "init_li malloc fail\n");
	return (SUCCESS);
}

int			main(int ac, char **av)
{
	t_li	li;

	ft_bzero(&li, sizeof(t_li));
	if (options(&li, --ac, ++av) == ERROR)
		return (ERROR);
	if (li.flags & FLAG_HELP)
		return (print_usage());
	init_li(&li);
	if (parsing(&li) != SUCCESS)
		return (ERROR);
	ft_putendl(li.buf);
	ants_init(&li);
	tree(&li);
	paths_opti_init(&li);
	path_init(&li);
	/* REVERSE */
	free_paths(&li.paths);
	free_paths(&li.paths_all);
	li.paths = ft_memalloc(sizeof(t_list_path));
	li.paths_all = ft_memalloc(sizeof(t_list_path));
	li.flags |= FLAG_REVERSE;
	path_init(&li);
	/* REVERSE */
	//repartition(&li, li.paths);
	repartition_lists(&li, li.paths_opti);
	ants_set_stage(&li);
	ants_move(&li);
	li.flags & FLAG_SOLUTION ? print_solution(&li, li.paths_opti[0]) : 0;
	free_all(&li);
	return (SUCCESS);
}
