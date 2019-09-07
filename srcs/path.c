/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 18:08:18 by chrhuang          #+#    #+#             */
/*   Updated: 2019/09/07 15:36:36 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**			Clear the path
**			Unreserve all rooms and delete all stages
*/

int			path_clear(t_path *path)
{
	t_stage	*stage;

	path->current = path->start;
	while (path->current)
	{
		stage = path->current;
		if (stage->room->path == path)
		{
			stage->room->flags &= ~FLAG_RESERVED;
			stage->room->path = NULL;
		}
		path->current = path->current->next;
		ft_memdel((void **)&stage);
	}
	return (SUCCESS);
}

/*
**			Insert stage at the beginning of the path
*/

static int	insert_stage(t_li *li, t_path *path, t_room *room)
{
	t_stage	*stage;

	if (!(stage = (t_stage *)malloc(sizeof(t_stage))))
		trigger_error(li, "Error malloc stage\n");
	ft_bzero(stage, sizeof(t_stage));
	stage->room = room;
	path->size++;
	if (!path->start)
	{
		path->start = stage;
		path->current = stage;
		path->end = stage;
		return (SUCCESS);
	}
	stage->next = path->start;
	path->start = stage;
	return (SUCCESS);
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
**			Duplicate a path
*/

t_path		*path_dup(t_path *path)
{
	t_path	*new;
	t_stage	*stage;

	if (!(new = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	ft_bzero(new, sizeof(t_path));
	path->current = path->start;
	while (path->current)
	{
		if (!(stage = (t_stage *)malloc(sizeof(t_stage))))
			return (NULL); //free new_path
		ft_bzero(stage, sizeof(t_stage));
		stage->room = path->current->room;
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
		path->current = path->current->next;
	}
	new->end = new->current;
	new->size = path->size;
	return (new);
}

/*
**			Create a path
*/

t_path		*path_new(t_li *li)
{
	t_path	*path;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		trigger_error(li, "Error malloc path\n");
	ft_bzero(path, sizeof(t_path));
	insert_stage(li, path, li->rooms->end);
	while (li->rooms->current && li->rooms->current != li->rooms->start)
	{
		insert_stage(li, path, li->rooms->current);
		li->rooms->current->flags |= FLAG_RESERVED;
		li->rooms->current = li->rooms->current->parent;
	}
	return (path);
}
