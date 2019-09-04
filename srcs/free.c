/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 20:35:55 by chrhuang          #+#    #+#             */
/*   Updated: 2019/09/04 17:21:28 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

static void	free_paths_list(t_list_path **lists)
{
	while (lists && *lists)
		free_paths(lists++);
}

static void	free_parents(t_room *room)
{
	while (room->parents && room->parents->first)
	{
		room->parents->current = room->parents->first;
		room->parents->first = room->parents->current->next;
		ft_memdel((void **)&room->parents->current);
	}
	ft_memdel((void **)&room->parents);
}

static void	free_childs(t_room *room)
{
	while (room->childs && room->childs->first)
	{
		room->childs->current = room->childs->first;
		room->childs->first = room->childs->current->next;
		ft_memdel((void **)&room->childs->current);
	}
	ft_memdel((void **)&room->childs);
}

static void	free_links(t_room *room)
{
	while (room->links && room->links->first)
	{
		room->links->current = room->links->first;
		room->links->first = room->links->current->next;
		ft_memdel((void **)&room->links->current);
	}
	ft_memdel((void **)&room->links);
}

static void	free_room(t_room **room_ptr)
{
	t_room	*room;

	if (!room_ptr || !*room_ptr)
		return ;
	room = *room_ptr;
	ft_memdel((void **)&room->name);
	free_links(room);
	free_parents(room);
	free_childs(room);
	ft_memdel((void **)room_ptr);
}

static void	free_rooms(t_li *li)
{
	while (li->rooms && li->rooms->start)
	{
		li->rooms->current = li->rooms->start;
		li->rooms->start = li->rooms->current->next;
		li->rooms->current == li->start ? li->start = NULL : 0;
		li->rooms->current == li->end ? li->end = NULL : 0;
		free_room(&li->rooms->current);
	}
	ft_memdel((void **)&li->rooms);
	free_room(&li->start);
	free_room(&li->end);
}

static void	free_matrice(t_li *li)
{
	int	i;

	i = 0;
	if (!li->matrice)
		return ;
	while (i < li->rooms->size)
		ft_memdel((void **)li->matrice + i++);
	ft_memdel((void **)&li->matrice);
}

int			free_all(t_li *li)
{
	if (!li)
		return (SUCCESS);
	ft_memdel((void **)&li->line);
	ft_free_tab(&li->line_split);
	ft_memdel((void **)&li->ants);
	ft_memdel((void **)&li->queue);
	ft_memdel((void **)&li->queue_res);
	free_paths(&li->paths_all);
	free_paths(&li->paths);
	if (li->paths_opti)
		free_paths_list(li->paths_opti + 1);
	ft_memdel((void **)&li->paths_opti);
	free_matrice(li);
	free_rooms(li);
	return (SUCCESS);
}
