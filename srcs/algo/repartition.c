/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repartition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 15:30:14 by sregnard          #+#    #+#             */
/*   Updated: 2019/09/10 09:57:25 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**			Set capacity of each path
**			If necessary, delete all paths that have invalid capacities,
**			then retry everything
*/

static int	set_capacity(t_list_path *paths, int *ants)
{
	t_path	*path;
	int		ret;

	ret = SUCCESS;
	paths->current = paths->first;
	while (paths->current)
	{
		paths->current->capacity = paths->turns - (paths->current->size - 1);
		if (paths->current->capacity <= 0)
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

/*
**			Fix rounding problems
*/

static int	leftovers(t_list_path *paths, int ants)
{
	paths->current = paths->first;
	if (ants)
		++paths->turns;
	while (paths->current && ants--)
	{
		++paths->current->capacity;
		paths->current = paths->current->next;
	}
	return (SUCCESS);
}

/*
**			Determine how many ants should be sent for each path
*/

int			repartition(t_li *li, t_list_path *paths)
{
	int		ants;
	int		diff;

	if (!paths || !paths->size)
		return (FAIL);
	ants = li->nb_ants;
	diff = ants - (paths->size - paths->sum);
	paths->turns = diff / paths->size;
	if (set_capacity(paths, &ants) == FAIL)
		return (repartition(li, paths));
	leftovers(paths, ants);
	return (SUCCESS);
}

int			repartition_lists(t_li *li, t_list_path **lists)
{
	int			i;

	i = 0;
	while (lists[++i])
		if (repartition(li, lists[i]) == FAILURE)
			trigger_error(li, "Repartition : FAILURE\n");
		else
		{
			if (!lists[0] || lists[0]->turns > lists[i]->turns)
				lists[0] = lists[i];
		}
	return (SUCCESS);
}
