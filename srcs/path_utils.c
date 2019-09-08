/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 14:35:20 by sregnard          #+#    #+#             */
/*   Updated: 2019/09/08 14:36:13 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Check if path already exists in given list of paths
*/

int	path_already_found(t_list_path *paths, t_path *path)
{
	paths->current = paths->first;
	while (paths->current)
	{
		if (path_cmp(paths->current, path) == SUCCESS)
			return (SUCCESS);
		paths->current = paths->current->next;
	}
	return (FAILURE);
}

/*
**	Check if given path has a collision with any path in li->paths
*/

int	path_collision(t_li *li, t_path *path)
{
	t_stage	*stage;

	if (!li->paths || !path)
		trigger_error(li, "Path collision : li->paths = NULL or path = NULL");
	stage = path->start;
	while (stage && stage->room != li->rooms->end)
	{
		if (stage->room->path)
			path_delete(li->paths, &stage->room->path);
		stage->room->path = path;
		stage->room->flags |= FLAG_RESERVED;
		stage = stage->next;
	}
	return (SUCCESS);
}

