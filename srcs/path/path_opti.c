/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_opti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:13:08 by chrhuang          #+#    #+#             */
/*   Updated: 2019/09/10 11:14:50 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Init shortest path
*/

int		paths_opti_init(t_li *li)
{
	if (!li->rooms->start->childs || !li->rooms->end->parents)
		trigger_error(li, "No link to start or end\n");
	li->max_path =
	(li->rooms->start->childs->size > li->rooms->end->parents->size ?
	li->rooms->end->parents->size : li->rooms->start->childs->size);
	if (!(li->paths_opti =
		ft_memalloc(sizeof(t_list_path *) * (li->max_path + 2))))
		trigger_error(li, "paths_opti_init : Malloc fail\n");
	return (SUCCESS);
}

/*
**	Delete path list
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
**	Keep best combinaison of paths
*/

int		paths_opti(t_li *li)
{
	t_list_path	*paths_dup;
	int			max_a;
	int			max_b;

	if (!(paths_dup = path_list_dup(li, li->paths)))
		trigger_error(li, "paths_opti : path_list_dup fail\n");
	repartition(li, paths_dup);
	li->paths->turns = paths_dup->turns;
	path_list_delete(&paths_dup);
	if (!li->paths_opti[li->paths->size])
	{
		if (!(li->paths_opti[li->paths->size] = path_list_dup(li, li->paths)))
			trigger_error(li, "paths_opti : path_list_dup fail\n");
		return (SUCCESS);
	}
	max_a = li->paths_opti[li->paths->size]->turns;
	max_b = li->paths->turns;
	if (max_a < max_b)
		return (SUCCESS);
	path_list_delete(&li->paths_opti[li->paths->size]);
	if (!(li->paths_opti[li->paths->size] = path_list_dup(li, li->paths)))
		trigger_error(li, "paths_opti : path_list_dup fail\n");
	return (SUCCESS);
}
