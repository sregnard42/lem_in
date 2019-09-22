/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 15:35:11 by chrhuang          #+#    #+#             */
/*   Updated: 2019/09/22 17:15:32 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**			Print usage
*/

int			print_usage(void)
{
	ft_printf("%-8s: %s\n", "usage", "./lem_in [options] < map");
	ft_printf("%-8s: %s\n", "options", "-t -> display turns");
	ft_printf("%-9s %s\n", "", "-c -> display colors");
	ft_printf("%-9s %s\n", "", "-p -> display solution");
	ft_printf("%-9s %s\n", "", "-d -> display debug message");
	return (ERROR);
}

/*
**			Print a path
*/

void		print_path(t_path *path)
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
		stage ? ft_putstr(" -> ") : ft_putstr(" ]\n");
	}
}

/*
**			Print Solution
*/

void		print_solution(t_li *li, t_list_path *paths)
{
	int	color;
	int	i;

	color = 32;
	paths->current = paths->first;
	i = 0;
	li->flags & FLAG_COLOR ? ft_printf("%s", CYAN) : 0;
	ft_printf("\nSolution :%s\n", RESET);
	li->flags & FLAG_COLOR ? 0 : (color = 0);
	while (paths->current)
	{
		ft_printf("%s", li->flags & FLAG_COLOR ? CYAN : RESET);
		ft_printf("[ %d ] %s", ++i, RESET);
		ft_printf("\033[1;%dm", color);
		print_path(paths->current);
		if (li->flags & FLAG_COLOR)
			color == 36 ? color = 32 : ++color;
		paths->current = paths->current->next;
	}
	ft_printf("%s", RESET);
}

/*
**			Print turn
*/

void		print_turn(t_li *li)
{
	static int	turn = 0;

	if (li->flags & FLAG_COLOR)
		ft_printf("%s", CYAN);
	if (li->flags & FLAG_TURN)
		li->flags & FLAG_SP ? 0 : ft_printf("[ %d ] ", ++turn);
	if (li->flags & FLAG_COLOR)
		ft_printf("%s", RESET);
}
