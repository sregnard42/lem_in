/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repartition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 15:30:14 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/09 13:06:43 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	get_ants(t_list_path *paths, int turns)
{
	int		ants = 0;

	paths->current = paths->first;
	while (paths->current)
	{
		ants += turns - (paths->current->size - 1);
		paths->current = paths->current->next;
	}
	return (ants);
}

static int	set_capacity(t_list_path *paths, int turns, int *ants)
{
	paths->current = paths->first;
	while (paths->current)
	{
		paths->current->capacity = turns - (paths->current->size - 1);
		*ants -= paths->current->capacity;
		paths->current = paths->current->next;
	}
	return (SUCCESS);
}

static int	leftovers(t_list_path *paths, int ants)
{
	paths->current = paths->first;
	while (paths->current && ants--)
	{
		++paths->current->capacity;
		paths->current = paths->current->next;
	}
	return (SUCCESS);
}

int			repartition(t_li *li, t_list_path *paths)
{
	static int	color = 32;
	int		ants;
	int		diff;
	int		turns;

	if (!paths)
		return (FAIL);
	ants = li->nb_ants;
	ft_printf("\033[1;%dm", color++);
	ft_printf("\nrepartiton : BEGIN\n");
	ft_printf("nb_ants = %d\tnb_paths = %d\n", ants, paths->size);
	diff = get_ants(paths, 0) - ants;
	diff < 0 ? diff = -diff : 0;
	turns = diff / paths->size;
	ft_printf("turns = %d\n", turns);
	set_capacity(paths, turns, &ants);
	leftovers(paths, ants);
	path_print_all(paths);
	ft_printf("repartiton : END\n");
	ft_printf("\033[0m");
	return (SUCCESS);
}

