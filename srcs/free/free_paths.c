/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 15:19:35 by chrhuang          #+#    #+#             */
/*   Updated: 2019/09/10 10:58:31 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_path(t_path **path_ptr)
{
	t_path	*path;

	if (!path_ptr || !*path_ptr)
		return ;
	path = *path_ptr;
	while (path->start)
	{
		path->current = path->start->next;
		ft_memdel((void **)&path->start);
		path->start = path->current;
	}
	ft_memdel((void **)path_ptr);
}

void	free_paths(t_list_path **paths_ptr)
{
	t_list_path	*paths;

	paths = *paths_ptr;
	while (paths && paths->first)
	{
		paths->current = paths->first;
		paths->first = paths->current->next;
		path_delete(paths, &paths->current);
	}
	ft_memdel((void **)paths_ptr);
}

void	free_paths_list(t_list_path **lists)
{
	while (lists && *lists)
		free_paths(lists++);
}
