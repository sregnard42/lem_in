/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:41:03 by chrhuang          #+#    #+#             */
/*   Updated: 2019/07/31 17:32:17 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_matrice(bool **matrice, int nb) // tmpmptmptmptmpmtmt A delete
{
	for (int j = 0; j < nb ; j++)
	{
		for (int i = 0; i < nb; i++)
			matrice[j][i] == false ? ft_putstr("\033[1;31m0\033[0m ")
			: ft_putstr("\033[1;32m1\033[0m ");
		ft_printf("\n");
	}
}

void	new_matrice(t_li *li, int nb)
{
	bool	**matrice;
	int		i;

	i = -1;
	if (!(matrice = malloc(sizeof(bool*) * nb)))
		trigger_error(li, "Error malloc matrice\n");
	while (++i < nb)
	{
		if (!(matrice[i] = malloc(sizeof(bool) * nb)))
			trigger_error(li, "Error malloc matrice\n");
		ft_bzero((void *)matrice[i], sizeof(bool) * nb);
	}
	li->matrice = matrice;
}
