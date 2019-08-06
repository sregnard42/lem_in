/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:36:35 by chrhuang          #+#    #+#             */
/*   Updated: 2019/08/06 16:06:51 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**
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
		{
			ft_printf("\033[1;31m");
			ft_printf("%s already in a path, deleting path...\n", stage->room->name);
			path_delete(li, &stage->room->path);
			ft_printf("\033[0m");
		}
		stage->room->path = path;
		stage->room->flags |= FLAG_RESERVED;
		stage = stage->next;
	}
	return (SUCCESS);
}

/*
**	Add path to list of paths
*/

int	path_add(t_li *li, t_path *path)
{
	if (!li->paths || !path)
		return (ERROR);
	++li->paths->size;
	if (!li->paths->first)
	{
		li->paths->first = path;
			li->paths->current = path;
		li->paths->last = path;
		return (SUCCESS);
	}
	li->paths->last->next = path;
	li->paths->last = path;
	return (SUCCESS);
}

/*
**	SUCCESS if path has been successfully deleted
**	FAILURE	if there is no path to delete
*/

void	path_delete(t_li *li, t_path **path_ptr)
{
	t_path	*path;
	t_path	*path_prev;
	t_path	*path_next;

	path = *path_ptr;
	path_prev = path->prev;
	path_next = path->next;
	path_clear(path);
	ft_memdel((void **)path_ptr);
	if (!(--li->paths->size))
	{
		ft_bzero(li->paths, sizeof(t_list_path));
		return ;
	}
	path == li->paths->first ? li->paths->first = path_next : 0;
	path_prev ? path_prev->next = path_next : 0;
	path_next ? path_next->prev = path_prev : 0;
	if (li->paths->size == 1)
	{
		li->paths->first = path_prev ? path_prev : path_next;
		li->paths->current = path_prev ? path_prev : path_next;
		li->paths->last = path_prev ? path_prev : path_next;
	}
}

/*
**	Init the list of paths
*/

int			path_init(t_li *li)
{
	int		max_path;
	t_path	*path;

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
			path_delete(li, &li->paths->last);
			continue ;
		}
		ft_printf("\033[1;32mBFS: PATH FOUND\n");
		room_clean(li);
		path = path_new(li);
		ft_printf("Path created : ");
		path_print(path);
		ft_printf("\033[0m\n");
		if (li->shortest_path)
		{
			if (path_cmp(path, li->shortest_path) == SUCCESS)
			{
				ft_printf("\npath_init : END\n");
				return (SUCCESS);
			}
		}
		else
			li->shortest_path = path_dup(path);
		path_collision(li, path);
		path_add(li, path);
	}
	ft_printf("\npath_init : END\n");
	return (SUCCESS);
}
