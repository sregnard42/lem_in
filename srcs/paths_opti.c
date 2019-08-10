/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_opti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:13:08 by chrhuang          #+#    #+#             */
/*   Updated: 2019/08/10 17:49:45 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Init shortest path
*/

int	paths_opti_init(t_li *li)
{
	li->max_path = (li->rooms->start->nb_child > li->rooms->end->parents->size ?
	li->rooms->end->parents->size : li->rooms->start->nb_child);
	if (!(li->paths_opti =
		malloc(sizeof(t_list_path *) * (li->max_path + 2))))
		trigger_error(li, "paths_opti_init : Malloc fail\n");
	ft_bzero(li->paths_opti, sizeof(t_list_path *) * (li->max_path + 2));
	return (SUCCESS);
}

/*
**	delete path list
*/

void	path_list_delete(t_list_path **paths)
{
	t_path		*current;
	t_path		*next;

	if (!paths || !*paths)
		return ;
	current = (*paths)->first;
	while (current)
	{
		next = current->next;
		path_delete(*paths, &current);
		current = next;
	}
	ft_memdel((void **)paths);
}

/*
**	Update longest_path
*/

int		longest_path(t_list_path *paths)
{
	t_path	*path;
	int		max;

	if (!paths->size)
	{
		paths->longest_path = NULL;
		return (SUCCESS);
	}
	max = paths->first->size;;
	paths->longest_path = paths->first;
	path = paths->first->next;
	while (path)
	{
		if (max < path->size)
		{
			max = path->size;
			paths->longest_path = path;
		}
		path = path->next;
	}
	return (SUCCESS);
}

/*
**	Shortest path
*/

int	paths_opti(t_li *li)
{
	int	max_a;
	int	max_b;

	//ft_printf("Nb paths : %d\n", li->paths->size);
	if (!li->paths_opti[li->paths->size])
	{
		if (!(li->paths_opti[li->paths->size] = path_list_dup(li->paths)))
			trigger_error(li, "paths_opti : path_list_dup fail\n");
		return (SUCCESS);
	}
	max_a = (li->paths_opti[li->paths->size])->longest_path->size;
	max_b = li->paths->longest_path->size;
	if (max_a < max_b)
		return (SUCCESS);
	//Je sais pas si j'ai bien free mon t_list_path, alors Merci de checker ça Stanley <3
	//Ici il faut faire la fonction de free une t_list_path
	path_list_delete(&li->paths_opti[li->paths->size]);
	if (!(li->paths_opti[li->paths->size] = path_list_dup(li->paths)))
		trigger_error(li, "paths_opti : path_list_dup fail\n");
	ft_printf("------------------\n");
	path_print_all(li->paths_opti[li->paths->size]);
	return (SUCCESS);
}

/*
**	Print all paths_opti
*/

void	print_paths_opti(t_li *li)
{
	static int	color = 32;
	int	i;

	i = 0;
	while (i <= li->max_path && li->paths_opti[i])
	{
		ft_printf("\033[1;%dm", color);
		color == 36 ? color = 32 : ++color;
		path_print_all(li->paths_opti[i++]);
	}
	ft_printf("\033[1;0m");
}
