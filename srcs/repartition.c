/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repartition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 15:30:14 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/08 15:14:31 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Set	the capacity of each path
*/

static int		set_capacity(t_list_path *paths, double x)
{
	t_path	*path;
	double	nb;

	path = paths->first;
	while (path)
	{
		nb = path->weight * x;
//		path->capacity = ((int)(nb * 10) % 10) >= 5 ? nb + 1 : nb;
		path->capacity = nb;
		path->nb_turn = nb + path->size -1;
		path = path->next;
	}
	return (SUCCESS);
}

/*
**	Set the weight of each path and return the sum
*/

static double	sum(t_list_path *paths)
{
	double	sum;
	t_path	*path;

	sum = 0;
	path = paths->first;
	while (path)
	{
		path->weight = (double)paths->longest_path->size / (double)path->size;
		sum += path->weight;
		path = path->next;
	}
	return (sum);
}

/*
**	Calculate ant capacity for each path
**	if A is the longest path
**	weightA = 1 ; weightB = lenA / lenB ; ... ; weightZ = lenA / lenZ
**	x = nb_ants / (weightA + weightB + ... + weightZ)
**	capA = weightA * x ; capB = weightB * x ; ... ; capZ = weightZ * x
*/

int				repartition(t_li *li, t_list_path *paths)
{
	double	x;

	if (!paths || !paths->size)
		return (FAILURE);
	if (paths->size == 1)
	{
		paths->first->weight = 1;
		paths->first->capacity = li->nb_ants;
		return (SUCCESS);
	}
	x = li->nb_ants / sum(paths);
	set_capacity(paths, x);
	return (SUCCESS);
}

