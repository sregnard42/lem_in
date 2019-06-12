/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:22:20 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/12 10:44:02 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

static int	get_ants(t_li *li, char **tab)
{
	if (li == NULL || tab == NULL)
		trigger_error(li, "li or tab == NULL in get_ants function\n");
	while (tab)
	{
		if (ft_isinteger(*tab))
			break;
		tab++;
	}
	li->ants = ants_init(ft_atoi(*tab));
	return (SUCCESS);
}

int	parsing(int ac, char **av, t_li *li)
{
	char	**tab_start;
	char	**tab;

	ac += 0;
	if ((tab_start = read_file(*av)) == NULL)
		trigger_error(li, "Error file\n");
	tab = tab_start;
	get_ants(li, tab);
	get_rooms(li, tab);
	return (SUCCESS);
}
