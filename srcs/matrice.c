/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:41:03 by chrhuang          #+#    #+#             */
/*   Updated: 2019/09/08 13:57:36 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//TMP
void	print_matrice(bool **matrice, int nb)
{
	for (int i = 0; i < nb; i++)
	{
		for (int j = 0; j < nb; j++)
			matrice[i][j] == false ? ft_printf("\033[1;31m%s\033[0m", "0 ")
			: ft_printf("\033[1;32m%s\033[0m", "1 ");
		ft_printf("\n");
	}
}

void	new_matrice(t_li *li, int nb)
{
	bool	**matrice;
	int		i;

	i = -1;
	if (!(matrice = (bool **)ft_memalloc(sizeof(bool*) * nb)))
		trigger_error(li, "Error malloc matrice\n");
	while (++i < nb)
		if (!(matrice[i] = (bool *)ft_memalloc(sizeof(bool) * nb)))
			trigger_error(li, "Error malloc matrice\n");
	li->matrice = matrice;
}
