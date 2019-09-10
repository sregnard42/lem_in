/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:36:35 by chrhuang          #+#    #+#             */
/*   Updated: 2019/09/10 11:08:49 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	path_list_dup_bis(t_list_path *new, t_list_path *paths)
{
	if (!new->first)
	{
		if (!(new->first = path_dup(paths->first)))
		{
			ft_memdel((void **)&new);
			return (ERROR);
		}
		new->current = new->first;
	}
	else
	{
		if (!(new->current->next = path_dup(paths->current)))
		{
			free_paths(&new);
			return (ERROR);
		}
		new->current->next->prev = new->current;
		new->current = new->current->next;
	}
	return (SUCCESS);
}

/*
**	Duplicate a list of paths
*/

t_list_path	*path_list_dup(t_li *li, t_list_path *paths)
{
	t_list_path	*new;

	if (!(new = ft_memalloc(sizeof(t_list_path))))
		trigger_error(li, "path_list_dup : malloc\n");
	new->size = paths->size;
	new->sum = paths->sum;
	paths->current = paths->first;
	while (paths->current)
	{
		if (path_list_dup_bis(new, paths) == ERROR)
			return (NULL);
		paths->current = paths->current->next;
	}
	new->last = new->current;
	return (new);
}

/*
**	Add path to list of paths
*/

int			path_add(t_list_path *paths, t_path *path)
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
		return (SUCCESS);
	}
	path->prev = paths->last;
	paths->last->next = path;
	paths->last = path;
	return (SUCCESS);
}

/*
**	SUCCESS if path has been successfully deleted
**	FAILURE	if there is no path to delete
*/

void		path_delete(t_list_path *paths, t_path **path_ptr)
{
	t_path	*path;
	t_path	*path_prev;
	t_path	*path_next;

	path = *path_ptr;
	path_prev = path->prev;
	path_next = path->next;
	path_clear(path);
	paths->sum -= path->size;
	if (!(--paths->size))
	{
		ft_memdel((void **)&path);
		return (ft_bzero(paths, sizeof(t_list_path)));
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
	ft_memdel((void **)&path);
}

/*
**	Init the list of paths
*/

int			path_init(t_li *li)
{
	t_path	*path;

	while (bfs(li) == SUCCESS)
	{
		room_clean(li);
		path = path_new(li);
		if (!li->paths_all->size)
			path_add(li->paths_all, path_dup(path)) == ERROR ?
			trigger_error(li, "Error path add\n") : 0;
		else if (path_already_found(li->paths_all, path) == SUCCESS)
		{
			path_clear(path);
			ft_memdel((void **)&path);
			return (SUCCESS);
		}
		else
			path_add(li->paths_all, path_dup(path));
		path_collision(li, path);
		path_add(li->paths, path) == ERROR ?
		trigger_error(li, "Error path add\n") : 0;
		paths_opti(li);
	}
	return (FAILURE);
}
