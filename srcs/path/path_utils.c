/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 14:35:20 by sregnard          #+#    #+#             */
/*   Updated: 2019/09/10 11:10:04 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**			Duplicate a path
*/

static void	path_dup_bis(t_path *new, t_stage *stage)
{
	if (!new->start)
	{
		new->start = stage;
		new->current = stage;
	}
	else
	{
		new->current->next = stage;
		new->current = new->current->next;
	}
}

/*
**			Duplicate a path
*/

t_path		*path_dup(t_path *path)
{
	t_path	*new;
	t_stage	*stage;

	if (!(new = (t_path *)ft_memalloc(sizeof(t_path))))
		return (NULL);
	path->current = path->start;
	while (path->current)
	{
		if (!(stage = (t_stage *)ft_memalloc(sizeof(t_stage))))
		{
			ft_memdel((void **)&stage);
			free_path(&new);
			return (NULL);
		}
		stage->room = path->current->room;
		path_dup_bis(new, stage);
		path->current = path->current->next;
	}
	new->end = new->current;
	new->size = path->size;
	return (new);
}

/*
**			Check if two paths are identical
*/

int			path_cmp(t_path *path_a, t_path *path_b)
{
	t_stage	*stage_a;
	t_stage	*stage_b;

	if (path_a->size != path_b->size)
		return (FAILURE);
	stage_a = path_a->start;
	stage_b = path_b->start;
	while (stage_a && stage_b)
	{
		if (stage_a->room != stage_b->room)
			return (FAILURE);
		stage_a = stage_a->next;
		stage_b = stage_b->next;
	}
	return (SUCCESS);
}

/*
**	Check if path already exists in given list of paths
*/

int			path_already_found(t_list_path *paths, t_path *path)
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

int			path_collision(t_li *li, t_path *path)
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
