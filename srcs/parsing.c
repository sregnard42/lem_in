/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:22:20 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/11 19:49:09 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

static int	get_nb_ants(t_li *li, char **tab)
{
	if (li == NULL || tab == NULL)
		trigger_error(li, "li or tab == NULL in get_nb_ants function\n");
	while (tab)
	{
		if (ft_isinteger(*tab))
			break;
		tab++;
	}
	li->ants = ants_init(ft_atoi(*tab));
	ft_printf("ants nb = %d\n", atoi(*tab));
	return (SUCCESS);
}

int	is_room(char **tab)
{
	while (*tab != NULL)
	{
		if (*tab[0] == '#')
			return (FAIL);
		++tab;
	}
	return (SUCCESS);
}

int	parsing(int ac, char **av, t_li *li)
{
	char	**tab_start;
	char	**tab;
	char	**current;

	if ((tab_start = read_file(*av)) == NULL)
		trigger_error(li, "La fonction de Stan ne marche pas (read_file)\n");
	//ft_print_tab(tab);
				// Ants
	tab = tab_start;
	get_nb_ants(li, tab);
	get_rooms(li, tab);
	//li->ants = ants_init();
	return (SUCCESS);
}
