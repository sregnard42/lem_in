/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 14:46:08 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/15 16:21:43 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	path_already_found(t_list_path *paths, t_path *path)
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
**			Insert stage at the beginning of the path
*/

static int	stage_new(t_li *li, t_path *path, t_room *room)
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
	path->end->next = stage;
	path->end = stage;
	return (SUCCESS);
}

/*
**			Create a path (pathfinding edition)
*/

static t_path		*path_new_pf(t_li *li)
{
	t_path	*path;
	t_room	*child;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		trigger_error(li, "Error malloc path\n");
	ft_bzero(path, sizeof(t_path));
	child = li->rooms->start->child;
	while (child)
	{
		stage_new(li, path, child);
		child = child->child;
	}
	ft_printf("Path found & created : ");
	path_print(path);
	return (path);
}


static int	new_path(t_li *li)
{
	t_path	*path;

	path = path_new_pf(li);
	if (path_already_found(li->pathfinding, path) == SUCCESS)
		trigger_error(li, "Path already found !\n");
	path_add(li->pathfinding, path);
	room_clean(li);
	return (SUCCESS);
}

static int	backtrack(t_li *li, t_room *room)
{
	if (!room->links)
		return (FAIL);
	room->links->current = room->links->first;
	while (room->links->current)
	{
		if ((room->links->current->flags & FLAG_CLOSED)
		|| (room->links->current->dst->flags & FLAG_VISITED)
		|| (room->links->current->dst == room->parent))
		{
			room->links->current = room->links->current->next;
			continue ;
		}
		room->child = room->links->current->dst;
		room->child->parent = room;
		room->flags |= FLAG_VISITED;
		if (room->child == li->rooms->end)
			return (new_path(li));
		backtrack(li, room->child);
		room->links->current = room->links->current->next;
	}
	return (SUCCESS);
}

int			pathfinding(t_li *li)
{
	room_clean(li);
	backtrack(li, li->rooms->start);
	return (SUCCESS);
}
