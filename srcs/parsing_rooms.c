/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 19:37:16 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/11 19:49:17 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

int	get_rooms(t_li *li, char **tab)
{
	t_list	*room;
	t_room	*tmp;
	t_point	pos;
	char	*name;

	while (*tab != NULL)
	{
		ft_strequ(START, *tab) ? li->start = tmp : 0;
		ft_strequ(END, *tab) ? li->end = tmp : 0;
		while (is_room(tab) == FAIL)
			++tab;
		//Ignorer ce qu'il faut
		// parser pour avoir pos et name
		tmp = room_new(name, pos);
		// Ajouter dans la liste chainer
		++tab;
	}
	return (SUCCESS);
}