/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:12:26 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/26 10:53:32 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	length_path(t_path *path)
{
	int	len;

	len = 0;
	while (path && ++len)
		path = path->next;
	return (len);
}

static void	reset_path_flags(t_path **path)
{
	t_path	*tmp;
//	t_link	*links;

	ft_printf("Mauvais chemin, bye bye les flags\n");
	tmp = *path;
	while (tmp)
	{
		ft_printf("reset %s\n", tmp->room->name);
		tmp->room->flags = 0;
		/*links = tmp->room->links_start;
		while (links)
		{
			links->flags = 0;
			links = links->next;
		}*/
		tmp = tmp->next;
	}
}

static int	shortest_path(t_ant *ant, t_path **path_new, t_path **path)
{
	if (!path || !(*path))
	{
		return (SUCCESS);
	}
	ft_putendl("Old path");
	path_print(*path);
	ft_putendl("New path");
	path_print(*path_new);
	if (length_path(*path) < length_path(*path_new))
	{
		reset_path_flags(path_new);
		ft_memdel((void **)path_new);
		return (SUCCESS);
	}
	reset_path_flags(path);
	ft_memdel((void **)path);
	ant->path_start = *path_new;
	ant->path = *path_new;
	ant->path_last = *path_new;
	while (ant->path_last)
		ant->path_last = ant->path_last->next;
	return (SUCCESS);
}

static int	first_path(t_li *li, t_ant *ant, t_room *room, int round)
{
	t_link *link;

	if (room == li->start)
		ft_printf("Yo\n");
	if (room->flags & FLAG_VISITED/* && room != li->start*/)
	{
		ft_printf("la room %s est ferme\n", room->name);
		return (FAIL);
	}
	if (room == li->end)
	{
		add_to_path(ant, room, round);
		ft_printf("Path found\n");
		return (SUCCESS);
	}
	room->flags |= FLAG_VISITED;
	link = room->links_start;
	while (link != NULL)
	{
		if (link->flags & FLAG_USED)
		{
			link = link->next;
			continue;
		}
		if (first_path(li, ant, link->dst, round + 1) == SUCCESS)
		{
			link->flags |= FLAG_USED;
			add_to_path(ant, room, round);
			return (SUCCESS);
		}
		link = link->next;
	}
	if (ant->path_start == NULL)
	{
		ft_printf("No path\n");
		return (FAIL);
	}
	return (SUCCESS);
}

void tmp_reset_rooms_flags(t_li *li)
{
	li->room = li->start;
	while (li->room != NULL)
	{
		li->room->flags = 0;
		li->room->links = li->room->links_start;
		while (li->room->links != NULL)
		{
			li->room->links->flags = 0;
			li->room->links = li->room->links->next;
		}
		li->room = li->room->next;
	}
}

int init_paths(t_li *li)
{
	int		cpt;
	int		round;
	t_path	*path;

	cpt = 0;
	round = 0;
	li->ants = li->ants_start;
	while (cpt < li->nb_ants)
	{
		while (li->ants)
		{
			path = NULL;
			while (first_path(li, li->ants, li->start, round) == SUCCESS)
			{
				ant_print(li->ants);
				path_print(li->ants->path_start);
				shortest_path(li->ants, &li->ants->path, &path);
				ft_putendl("Path kept :");
				ant_print(li->ants);
				path_print(li->ants->path_start);
				path = li->ants->path_start;
				li->ants->path_start = NULL;
				li->start->flags = 0;
			}
			if (!path)
				break ;
			cpt++;
			ft_printf("\nchange ants\n\n");
			li->ants->path_start = path;
			li->ants = li->ants->next;
			li->start->flags = 0;
			path = NULL;
			//for (t_room *tmp = li->start; tmp; tmp = tmp->next)
			//	room_print(tmp);
		}
		ft_printf("\n------------------\nchange round\n------------------\n\n");
		tmp_reset_rooms_flags(li);
		round++;
	}
	li->ants = li->ants_start;
	while (li->ants)
	{
		ant_print(li->ants);
		if (li->ants->path)
			path_print(li->ants->path);
		else
			ft_putendl("No path");
		li->ants = li->ants->next;
	}
	return (SUCCESS);
}
