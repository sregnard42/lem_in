/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:13:08 by chrhuang          #+#    #+#             */
/*   Updated: 2019/08/07 14:14:10 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Init shortest path
*/

int	shortest_path_init(t_li *li)
{
	li->max_path = (li->rooms->start->nb_child > li->rooms->end->parents->size ?
	li->rooms->end->parents->size : li->rooms->start->nb_child);
	if (!(li->shortest_path = malloc(sizeof(t_list_path *) * li->max_path + 1)))
		trigger_error(li, "Shortest_path_init : Malloc fail\n");
	ft_bzero(li->shortest_path, sizeof(t_list_path) * li->max_path);
	return (SUCCESS);
}

/*
**	Fonction à supprimer car on peux l'opti
*/

int	path_list_len(t_list_path *list) //Ahah regarde le commentaire au dessus :D
{
	int	max;

	list->current = list->first;
	while (list->current)
	{
		if (max < list->current->size)
			max = list->current->size;
		list->current = list->current->next;
	}
	return (max);
}

/*
**	Shortest path
*/

int	shortest_path(t_li *li)
{
	int	max_a;
	int	max_b;

	//ft_printf("Nb paths : %d\n", li->paths->size);
	if (!li->shortest_path[li->paths->size])
	{
		if (!(li->shortest_path[li->paths->size] = path_list_dup(li->paths)))
			trigger_error(li, "Shortest_path : path_list_dup fail\n");
		return (SUCCESS);
	}
	max_a = path_list_len(li->shortest_path[li->paths->size]); //On peux opti ça
	max_b = path_list_len(li->paths);
	if (max_a < max_b)
		return (SUCCESS);
	//Je sais pas si j'ai bien free mon t_list_path, alors Merci de checker ça Stanley <3
	//Ici il faut faire la fonction de free une t_list_path
	if (!(li->shortest_path[li->paths->size] = path_list_dup(li->paths)))
		trigger_error(li, "Shortest_path : path_list_dup fail\n");
	ft_printf("------------------\n");
	path_print_all(li->shortest_path[li->paths->size]);
	return (SUCCESS);
}

/*
**	Print all shortest_path
*/

void	print_shortest_paths(t_li *li)
{
	int	i;

	i = 0;
	ft_printf("\033[1;31m");
	while (++i <= li->max_path)
	{
		if (!li->shortest_path[i])
			break ;
		ft_printf("Size : %d\n", li->shortest_path[i]->size);
		path_print_all(li->shortest_path[i]);
		ft_printf("----------\n");
	}
	ft_printf("\033[1;0m");
}
