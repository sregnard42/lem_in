/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 15:35:11 by chrhuang          #+#    #+#             */
/*   Updated: 2019/09/07 15:40:32 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**			Print a path
*/

void		path_print(t_path *path)
{
	t_stage *stage;

	ft_printf("[ %s = %3d ]", "len", path->size);
	ft_printf("[ %s = %4d ]", "capacity", path->capacity);
	stage = path->start;
	stage ? ft_putstr("[ ") : ft_putstr("[ No path ]\n");
	while (stage)
	{
		ft_printf("%s", stage->room->name);
		stage = stage->next;
		stage ?ft_putstr(" -> ") : ft_putstr(" ]\n");
	}
}

void		path_print_all(t_list_path *paths)
{
	int		sum_capacity;

	sum_capacity = 0;
	paths->current = paths->first;
	if (!paths->current)
	{
		ft_printf("<<<<<<<<<<<<<<<<<<<<<<< No path >>>>>>>>>>>>>>>>>>>>>>>\n");
		return ;
	}
	ft_printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	while (paths->current)
	{
		sum_capacity += paths->current->capacity;
		path_print(paths->current);
		paths->current = paths->current->next;
	}
	ft_printf("Sum length : %d\n", paths->sum);
	ft_printf("Total capacity : %d\n", sum_capacity);
	ft_printf("Nb of paths : %d\n", paths->size);
	ft_printf("Nb of turns : %d\n", paths->turns);
	ft_printf("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n");
}
