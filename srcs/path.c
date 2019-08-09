/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 18:08:18 by chrhuang          #+#    #+#             */
/*   Updated: 2019/08/09 14:31:34 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**			Clear the path
**			Unreserved all rooms and delete all stages
*/

int			path_clear(t_path *path)
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
**			Insert stage at the beginning of the path
*/

static int	insert_stage(t_li *li, t_path *path, t_room *room)
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
	stage->next = path->start;
	path->start = stage;
	return (SUCCESS);
}

/*
**			Check if two paths are identical
*/

int			path_cmp(t_path *path_a, t_path *path_b)
{
	t_stage	*stage_a;
	t_stage	*stage_b;

//	path_print(path_a);
//	path_print(path_b);
	if (path_a->size != path_b->size)
		return (FAILURE);
	stage_a = path_a->start;
	stage_b = path_b->start;
	while (stage_a && stage_b)
	{
		if (stage_a->room != stage_b->room)
			return (FAILURE);
		stage_a = stage_a->next;
		stage_b = stage_b->next;
	}
	return (SUCCESS);
}

/*
**			Duplicate a path
*/

t_path		*path_dup(t_path *path)
{
	t_path	*new;
	t_stage	*stage;

	if (!(new = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	ft_bzero(new, sizeof(t_path));
	path->current = path->start;
	while (path->current)
	{
		if (!(stage = (t_stage *)malloc(sizeof(t_stage))))
			return (NULL); //free new_path
		ft_bzero(stage, sizeof(t_stage));
		stage->room = path->current->room;
		if (!new->start)
		{
			new->start = stage;
			new->current = stage;
		}
		else
		{
			new->current->next = stage;
			new->current = new->current->next;
		}
		path->current = path->current->next;
	}
	new->end = new->current;
	new->size = path->size;
	return (new);
}

/*
**			Create a path
*/

t_path		*path_new(t_li *li)
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
	ft_printf("Path created\n");
	return (path);
}

/*
**			Print a path
*/

void		path_print(t_path *path)
{
	t_stage *stage;

	ft_printf("[ %s = %3d ]", "len", path->size);
	ft_printf("[ %s = %4d ]\t", "capacity", path->capacity);
	stage = path->start;
	stage ? ft_putstr("[ ") : ft_putstr("[ No path ]\n");
	while (stage)
	{
		ft_printf("%s", stage->room->name);
		stage = stage->next;
		stage ?ft_putstr(" -> ") : ft_putstr(" ]\t");
	}
	path->capacity < 0 ? ft_printf("[ X ]\n") : ft_putln();
}

void		path_print_all(t_list_path *paths)
{
	int		sum_capacity;

	sum_capacity = 0;
	paths->longest_path ? ft_printf("Max length : %d\n",
	paths->longest_path->size) : 0;
	paths->current = paths->first;
	while (paths->current)
	{
		sum_capacity += paths->current->capacity;
		path_print(paths->current);
		paths->current = paths->current->next;
	}
	ft_printf("Sum capacity : %d\n", sum_capacity);
}
