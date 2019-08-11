/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:53:46 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/11 13:11:45 by sregnard         ###   ########.fr       */
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

int			main(void)
{
	t_li	li;

	init_li(&li);
	if (parsing(&li) != SUCCESS)
		return (ERROR);
	ants_init(&li);
	/*************
	  ALGO START
	*************/
	// BFS BEGIN
	ft_printf("\033[1m");
	ft_printf("---Path init-----------------------------------------------\n");
	ft_printf("\033[0m");
	tree(&li);
	paths_opti_init(&li);
	path_init(&li);
	ft_printf("\033[1m");
	ft_printf("---Path init END-------------------------------------------\n");
	ft_printf("\033[0m");
	// BFS END
	// REPARTITION BEGIN
	ft_printf("\033[1;36m");
	ft_printf("---Repartition---------------------------------------------\n");
	repartition(&li, li.paths);
	for (int i = 1; i <= li.max_path; i++)
	{
		if (!li.paths_opti[i])
			break ;
		repartition(&li, li.paths_opti[i]);
		if (!li.paths_opti[0] ||
			li.paths_opti[0]->turns > li.paths_opti[i]->turns)
			li.paths_opti[0] = li.paths_opti[i];
	}
	ft_printf("---Repartition END-----------------------------------------\n");
	ft_printf("\033[0m");
	// REPARTITION END
	/*************
	  ALGO END
	*************/
	ft_printf("\033[1m");
	ft_printf("---Summary-------------------------------------------------\n");
	ft_printf("Nb ants : %d\n", li.nb_ants);
	ft_printf("-----------------------------------------------------------\n");
	ft_printf("All individual paths found :\n");
	path_print_all(li.paths_all);
	ft_printf("-----------------------------------------------------------\n");
	ft_printf("Last set of compatible paths found :\n");
	path_print_all(li.paths);
	ft_printf("-----------------------------------------------------------\n");
	ft_printf("All sets of compatible paths kept :\n");
	print_paths_opti(&li);
	ft_printf("\033[1m");
	ft_printf("---Summary END---------------------------------------------\n");
	ft_printf("---Moving ants---------------------------------------------\n");
	ft_printf("\033[0m");
	ants_set_stage(&li);
	ants_move(&li);
	ft_printf("\033[1m");
	ft_printf("---Moving ants END-----------------------------------------\n");
	ft_printf("Set of paths used :\n");
	path_print_all(li.paths_opti[0]);
	ft_printf("\033[0m");
//	free_all(&li);
	return (SUCCESS);
}
