/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 19:37:16 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/11 22:23:58 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

static int	is_room(t_li *li, char **tab)
{
	char	**tmp;

	ft_strequ(START, *tab) ? li->flags |= FLAG_START : 0;
	//li->flags & FLAG_START ? ft_putendl("start") : 0;
	li->flags &= ~FLAG_START;
	ft_strequ(END, *tab) ? li->flags |= FLAG_END : 0;
	//li->flags & FLAG_END ? ft_putendl("end") : 0;
	li->flags &= ~FLAG_END;
	if (*tab[0] == '#')
		return (FAIL);
	else if ((ft_nb_str_tab(tmp = ft_strsplit(*tab, ' '))) != 3) // Tu as dit que c'etait a la norme, c'est pas ma faute :D
	{
		ft_free_tab(&tmp);
		return (FAIL);
	}
	else if (!ft_isinteger(tmp[1]) || !ft_isinteger(tmp[2]))
	{
		ft_free_tab(&tmp);
		return (FAIL);
	}
	else
		return (SUCCESS);
}

int	get_rooms(t_li *li, char **tab)
{
	t_list	*rooms;
	t_list	*new;
	t_room	*tmp;
	t_point	pos;
	char	**room;

	rooms = NULL;
	while (*tab != NULL)
	{
		ft_strequ(START, *tab) ? li->start = tmp : 0;
		ft_strequ(END, *tab) ? li->end = tmp : 0;
		while (*tab != NULL && is_room(li, tab) == FAIL)
		{
			ft_printf("no rooms = %s\n", *tab);
			++tab;
		}
		ft_printf("is a room = %s\n", *tab);
		if (*tab == NULL)
			break;
		room = ft_strsplit(*tab, ' ');
		tmp = room_new(room[0], (t_point){ft_atoi(room[1]), ft_atoi(room[2])});
		new = ft_lstnew(tmp, sizeof(tmp));
		ft_printf("new = %p\n", new);
		rooms == NULL ? rooms = new : ft_lstadd(&rooms, new);
		//Ignorer ce qu'il faut
		// parser pour avoir pos et name
		//tmp = room_new(name, pos);
		// Ajouter dans la liste chainer
		if (*tab != NULL)
			++tab;
	}
	while (rooms != NULL)
	{
		ft_printf("%p\n", rooms->content); //Je veut afficher mais j'y arrive pas a cause du void * :(
		rooms = rooms->next;
	}
	return (SUCCESS);
}
