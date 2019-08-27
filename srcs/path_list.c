/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:36:35 by chrhuang          #+#    #+#             */
/*   Updated: 2019/08/27 14:43:59 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Duplicate a t_list_path
*/

t_list_path	*path_list_dup(t_list_path *paths)
{
	t_list_path	*new;

	if (!(new = malloc(sizeof(t_list_path))))
		return (NULL);
	ft_bzero(new, sizeof(t_list_path));
	new->size = paths->size;
	paths->current = paths->first;
	while (paths->current)
	{
		if (!new->first)
		{
			new->first = path_dup(paths->first);
			new->current = new->first;
			new->longest_path = new->first;
		}
		else
		{
			new->current->next = path_dup(paths->current);
			new->current->next->prev = new->current;
			new->current = new->current->next;
			if (new->current->size > new->longest_path->size)
				new->longest_path = new->current;
		}
		paths->current = paths->current->next;
	}
	new->sum = paths->sum;
	new->last = new->current;
	paths->current = paths->first;
	new->current = new->first;
	return (new);
}

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
			//ft_printf("\033[1;31m");
			//ft_printf("%s already in a path, deleting older path...\n", stage->room->name);
			path_delete(li->paths, &stage->room->path);
			//ft_printf("\033[0m");
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

int	path_add(t_list_path *paths, t_path *path)
{
	if (!paths || !path)
		return (ERROR);
	++paths->size;
	paths->sum += path->size;
	if (!paths->first)
	{
		paths->first = path;
		paths->current = path;
		paths->last = path;
		paths->longest_path = path;
		return (SUCCESS);
	}
	path->prev = paths->last;
	paths->last->next = path;
	paths->last = path;
	if (paths->longest_path->size < path->size)
		paths->longest_path = path;
	return (SUCCESS);
}

/*
**	SUCCESS if path has been successfully deleted
**	FAILURE	if there is no path to delete
*/

void	path_delete(t_list_path *paths, t_path **path_ptr)
{
	t_path	*path;
	t_path	*path_prev;
	t_path	*path_next;

	path = *path_ptr;
	path_prev = path->prev;
	path_next = path->next;
	path_clear(path);
	if (!(--paths->size))
	{
		ft_memdel((void **)&path);
		ft_bzero(paths, sizeof(t_list_path));
		return ;
	}
	path == paths->first ? paths->first = path_next : 0;
	path == paths->last ? paths->last = path_prev : 0;
	path_prev ? path_prev->next = path_next : 0;
	path_next ? path_next->prev = path_prev : 0;
	if (paths->size == 1)
	{
		paths->first = path_prev ? path_prev : path_next;
		paths->current = path_prev ? path_prev : path_next;
		paths->last = path_prev ? path_prev : path_next;
	}
	path == paths->longest_path ? longest_path(paths) : 0;
	paths->sum -= path->size;
	ft_memdel((void **)&path);
}

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
**	Init the list of paths
*/

int			path_init(t_li *li)
{
	static int	color = 32;
	t_path	*path;

	while (bfs(li) == SUCCESS)
	{
		//ft_printf("\033[1;%dm", color);
		//ft_printf("BFS: Path found\n");
		room_clean(li);
		path = path_new(li);
		//ft_printf("\033[0m");
		if (!li->paths_all->size)
			path_add(li->paths_all, path_dup(path));
		else if (path_already_found(li->paths_all, path) == SUCCESS)
		{
			//ft_printf("\033[1;31m");
			//ft_printf("Already found ! All paths found !\n");
			path_clear(path);
			//ft_printf("\033[0m");
			ft_memdel((void **)&path);
			return (SUCCESS);
		}
		else
			path_add(li->paths_all, path_dup(path));
		path_collision(li, path);
		path_add(li->paths, path);
//		ft_printf("\033[1;%dm", color);
//		ft_printf(":: Paths updated ::\n", color);
//		path_print_all(li->paths);
		paths_opti(li);
//		ft_printf("\033[0m");
		color == 36 ? color = 32 : ++color;
	}
	ft_printf("BFS FAILED\n");
	return (FAILURE);
}
