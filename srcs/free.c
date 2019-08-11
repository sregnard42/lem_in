/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 20:35:55 by chrhuang          #+#    #+#             */
/*   Updated: 2019/08/11 16:57:49 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	free_paths(t_list_path **paths_ptr)
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

static void	free_paths_list(t_list_path **lists)
{
	while (lists && *lists)
		free_paths(lists++);
}

static void	free_parents(t_li *li)
{
	t_room	*room;

	room = li->rooms->current;
	while (room->parents && room->parents->first)
	{
		room->parents->current = room->parents->first;
		room->parents->first = room->parents->current->next;
		ft_memdel((void **)&room->parents->current);
	}
}

static void	free_links(t_li *li)
{
	t_room	*room;

	room = li->rooms->current;
	while (room->links && room->links->first)
	{
		room->links->current = room->links->first;
		room->links->first = room->links->current->next;
		ft_memdel((void **)&room->links->current);
	}
	ft_memdel((void **)&room->links);
}

static void	free_rooms(t_li *li)
{
	while (li->rooms && li->rooms->start)
	{
		li->rooms->current = li->rooms->start;
		li->rooms->start = li->rooms->current->next;
		ft_memdel((void **)&li->rooms->current->name);
		free_links(li);
		free_parents(li);
		ft_memdel((void **)&li->rooms->current);
	}
	ft_memdel((void **)&li->rooms);
}

static void	free_matrice(t_li *li)
{
	int	i;

	i = 0;
	while (i < li->rooms->size)
		ft_memdel((void **)li->matrice + i++);
	ft_memdel((void **)&li->matrice);
}

int			free_all(t_li *li)
{
	if (!li)
		return (SUCCESS);
	ft_printf("FREE ALL THE THINGS\n");
	ft_memdel((void **)&li->ants);
	ft_memdel((void **)&li->queue);
	ft_memdel((void **)&li->queue_res);
	free_paths(&li->paths_all);
	free_paths(&li->paths);
	free_paths_list(li->paths_opti + 1);
	ft_memdel((void **)&li->paths_opti);
	free_matrice(li);
	free_rooms(li);
	ft_printf("FREED ALL THE THINGS ?\n");
	return (SUCCESS);
}
