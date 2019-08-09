/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repartition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 15:30:14 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/09 14:39:36 by sregnard         ###   ########.fr       */
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
	t_path	*path;
	int		ret;

	ret = SUCCESS;
	paths->current = paths->first;
	while (paths->current)
	{
		paths->current->capacity = turns - (paths->current->size - 1);
		if (paths->current->capacity < 0)
		{
			ret = FAIL;
			path = paths->current->next;
			path_delete(paths, &paths->current);
			paths->current = path;
			continue ;
		}
		*ants -= paths->current->capacity;
		paths->current = paths->current->next;
	}
	return (ret);
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
	int		ants;
	int		diff;
	int		turns;

	if (!paths)
		return (FAIL);
	ants = li->nb_ants;
	diff = get_ants(paths, 0) - ants;
	diff < 0 ? diff = -diff : 0;
	turns = diff / paths->size;
	if (set_capacity(paths, turns, &ants) == FAIL)
		return (repartition(li, paths));
	leftovers(paths, ants);
	return (SUCCESS);
}

