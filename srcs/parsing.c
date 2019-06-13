/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:22:20 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/13 15:41:59 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

static int	get_ants(t_li *li, char *line, int *nb_ants)
{
	if (li == NULL || line == NULL)
		trigger_error(li, "li or tab == NULL in get_ants function\n");
	if (*line == '#')
		return (FAIL);
	if (!ft_isinteger(line))
		trigger_error(li, "not integerake");
	*nb_ants = ft_atoi(line);
	li->flags &= ~FLAG_ANT;
	li->flags |= FLAG_ROOM;
	return (SUCCESS);
}

int	parsing(t_li *li)
{
	char	*line;
	int		nb_ants;
	t_room	*last;

	line = NULL;
	li->flags |= FLAG_ANT;
	while (li->flags & FLAG_ANT && get_next_line(0, &line))
	{
		get_ants(li, line, &nb_ants);
		ft_memdel((void **)&line);
	}
	while (get_next_line(0, &line))
	{
		li->flags & FLAG_ROOM ? get_room(li, line, &last) : 0;
		li->flags & FLAG_LINK ? get_link(li, line) : 0;
		ft_memdel((void **)&line);
	}
	ants_init(li->start, nb_ants);
	ft_printf("start name = %s\nname = %s\n", li->start->name, li->room->name);
	//li->room->prev = li->start;
	li->room = li->start;
	li->start->prev = NULL;
	return (SUCCESS);
}
