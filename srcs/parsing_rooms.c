/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 19:37:16 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/11 19:57:26 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

static int	is_room(t_li *li, char **tab)
{
	ft_strequ(START, *tab) ? li->flags |= FLAG_START : 0;
	li->flags & FLAG_START ? ft_putendl("start") : 0;
	li->flags &= ~FLAG_START;
	ft_strequ(START, *tab) ? li->flags |= FLAG_END : 0;
	li->flags & FLAG_START ? ft_putendl("end") : 0;
	li->flags &= ~FLAG_END;
	while (*tab != NULL)
	{
		if (*tab[0] == '#')
			return (FAIL);
		++tab;
	}
	return (SUCCESS);
}

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
		while (is_room(li, tab) == FAIL)
			++tab;
		//Ignorer ce qu'il faut
		// parser pour avoir pos et name
		tmp = room_new(name, pos);
		// Ajouter dans la liste chainer
		++tab;
	}
	return (SUCCESS);
}
