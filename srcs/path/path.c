/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 18:08:18 by chrhuang          #+#    #+#             */
/*   Updated: 2019/09/10 10:21:58 by chrhuang         ###   ########.fr       */
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

	if (!(stage = (t_stage *)ft_memalloc(sizeof(t_stage))))
		trigger_error(li, "Error malloc stage\n");
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
**			Create a path
*/

t_path		*path_new(t_li *li)
{
	t_path	*path;

	if (!(path = (t_path *)ft_memalloc(sizeof(t_path))))
		trigger_error(li, "Error malloc path\n");
	insert_stage(li, path, li->rooms->end);
	while (li->rooms->current && li->rooms->current != li->rooms->start)
	{
		insert_stage(li, path, li->rooms->current);
		li->rooms->current->flags |= FLAG_RESERVED;
		li->rooms->current = li->rooms->current->parent;
	}
	return (path);
}
