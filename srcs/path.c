/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 18:08:18 by chrhuang          #+#    #+#             */
/*   Updated: 2019/08/05 23:23:52 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Clear the path
**	Unreserved all rooms and delete all stages
*/

static int	path_clear(t_path *path)
{
	t_stage	*stage;

	path->current = path->start;
	ft_printf("Path clearing...\n");
	while (path->current)
	{
		stage = path->current;
		ft_printf("Clearing stage : %s\n", stage->room->name);
		stage->room->flags &= ~FLAG_RESERVED;
		stage->room->weight++;
		stage->room->path = NULL;
		path->current = path->current->next;
		ft_memdel((void **)&stage);
	}
	ft_printf("Path cleared\n");
	return (SUCCESS);
}

/*
**	SUCCESS if path has been successfully deleted
**	FAILURE	if there is no path to delete
*/

static int	path_delete(t_li *li, t_path **path_ptr)
{
	t_path	*path;
	t_path	*path_prev;
	t_path	*path_next;

	path = *path_ptr;
	path_prev = path->prev;
	path_next = path->next;
	path_clear(path);
	li->paths->size--;
	if (!li->paths->size)
	{
		ft_bzero(li->paths, sizeof(t_list_path));
		return (SUCCESS);
	}
	if (path_prev)
		path_prev->next = path_next;
	if (path_next)
		path_next->prev = path_prev;
	if (li->paths->size == 1)
	{
		li->paths->first = path_prev ? path_prev : path_next;
		li->paths->current = path_prev ? path_prev : path_next;
		li->paths->last = path_prev ? path_prev : path_next;
	}
	return (SUCCESS);
}

/*
**	Insert stage at the beginning of the path
*/

static int	insert_stage(t_li *li, t_path *path, t_room *room)
{
	t_stage	*stage;

	if (!(stage = (t_stage *)malloc(sizeof(t_stage))))
		trigger_error(li, "Error malloc stage\n");
	ft_bzero(stage, sizeof(t_stage));
	stage->room = room;
	if (room->path && room != li->rooms->end)
	{
		ft_printf("%s already in a path, deleting path...\n", room->name);
		path_delete(li, &room->path);
	}
	room->path = path;
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
**	Add path to the list of paths
*/

static int	path_new(t_li *li)
{
	t_path	*path;

	ft_printf("Path creation...\n");
	if (!(path = (t_path *)malloc(sizeof(t_path))))
		trigger_error(li, "Error malloc path\n");
	ft_bzero(path, sizeof(t_path));
	insert_stage(li, path, li->rooms->end);
	while (li->rooms->current && li->rooms->current != li->rooms->start)
	{
		insert_stage(li, path, li->rooms->current);
		li->rooms->current->flags |= FLAG_RESERVED;
		li->rooms->current->weight--;
		li->rooms->current = li->rooms->current->parent;
	}
	li->paths->size++;
	if (!li->paths->first)
	{
		li->paths->first = path;
		li->paths->current = path;
		li->paths->last = path;
		ft_printf("Path created\n");
		return (SUCCESS);
	}
	path->prev = li->paths->last;
	li->paths->last->next = path;
	li->paths->last = path;
	ft_printf("Path created\n");
	return (SUCCESS);
}

/*
**	Init the list of paths
*/

int			path_init(t_li *li)
{
	int	max_path;

	ft_printf("path_init : BEGIN\n\n");
	max_path = (li->rooms->start->nb_child > li->rooms->end->parents->size ?
	li->rooms->end->parents->size : li->rooms->start->nb_child);
	while (max_path > li->paths->size)
	{
		if (bfs_maxflow(li) == FAIL)
		{
			ft_printf("\033[1;31mBFS: NO PATH\n");
			room_clean(li);
			li->paths->last ? ft_printf("Delete last path : ")
			: ft_printf("No path to delete...\n");
			li->paths->last ? path_print(li->paths->last) : 0;
			ft_printf("\033[0m\n");
			if (path_delete(li, &li->paths->last) == FAILURE)
			{
				ft_printf("path_init : END\n");
				return (FAILURE);
			}
			continue ;
		}
		ft_printf("\033[1;32mBFS: PATH FOUND\n");
		room_clean(li);
		path_new(li);
		path_print(li->paths->last);
		ft_printf("\033[0m\n");
	}
	ft_printf("li->paths->size : %d\n", li->paths->size);
	path_print_all(li->paths);
	ft_printf("path_init : END\n");
	return (SUCCESS);
}

void		path_print(t_path *path)
{
	t_stage *stage;

	stage = path->start;
	while (stage)
	{
		ft_printf("%s", stage->room->name);
		stage = stage->next;
		stage ? ft_putstr(" -> ") : ft_putstr("\n");
	}
}

void		path_print_all(t_list_path *paths)
{
	paths->current = paths->first;
	while (paths->current)
	{
		path_print(paths->current);
		paths->current = paths->current->next;
	}
}
