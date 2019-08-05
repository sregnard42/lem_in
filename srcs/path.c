/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 18:08:18 by chrhuang          #+#    #+#             */
/*   Updated: 2019/08/05 20:27:59 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	insert_stage(t_li *li, t_path *path, t_room *room)
{
	t_stage	*stage;

	if (!(stage = (t_stage *)malloc(sizeof(t_stage))))
		trigger_error(li, "Error malloc stage\n");
	ft_bzero(stage, sizeof(t_stage));
	stage->room = room;
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

static int	path_new(t_li *li)
{
	t_path	*path;

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
	path_print(path);
	if (!li->paths->start)
	{
		li->paths->start = path;
		li->paths->current = path;
		li->paths->end = path;
		return (SUCCESS);
	}
	li->paths->end->next = path;
	li->paths->end = path;
	return (SUCCESS);
}

int			path_init(t_li *li)
{
	int	max_path;

	ft_printf("path_init : BEGIN\n");
	max_path = (li->rooms->start->nb_child > li->rooms->end->parents->size ?
	li->rooms->end->parents->size : li->rooms->start->nb_child);
	ft_printf("max path = %d\n", max_path);
	while (max_path > li->paths->size)
	{
		if (bfs_maxflow(li, 0) == FAIL)
		{
			ft_printf("\033[1;31mBFS: NO PATH\033[0m\n");
			room_clean(li, li->rooms->start);
			break ;
		}
		ft_printf("\033[1;32mBFS: PATH FOUND\033[0m\n");
		path_new(li);
	}
	ft_printf("path_init : END\n");
	return (SUCCESS);
}

void		path_print(t_path *path)
{
	t_stage *stage;

	stage = path->start;
	while (stage)
	{
		ft_printf("%s[%d]", stage->room->name, stage->turn);
		stage = stage->next;
		stage ? ft_putstr("->") : ft_putstr("\n");
	}
}
