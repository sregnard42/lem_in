/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 20:35:55 by chrhuang          #+#    #+#             */
/*   Updated: 2019/09/08 15:25:48 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	free_matrice(t_li *li)
{
	int	i;

	i = 0;
	if (!li->links)
		return ;
	while (i < li->rooms->size)
		ft_memdel((void **)li->links + i++);
	ft_memdel((void **)&li->links);
}

int			free_all(t_li *li)
{
	if (!li)
		return (SUCCESS);
	ft_memdel((void **)&li->line);
	ft_free_tab(&li->line_split);
	ft_memdel((void **)&li->ants);
	ft_memdel((void **)&li->queue);
	ft_memdel((void **)&li->queue_res);
	free_paths(&li->paths_all);
	free_paths(&li->paths);
	if (li->paths_opti)
		free_paths_list(li->paths_opti + 1);
	ft_memdel((void **)&li->paths_opti);
	free_matrice(li);
	free_rooms(li);
	return (SUCCESS);
}
