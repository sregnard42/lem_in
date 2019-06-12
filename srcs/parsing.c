/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:22:20 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/12 14:58:25 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

static int	get_ants(t_li *li, char *line, int *nb_ants)
{
	if (li == NULL || line == NULL)
		trigger_error(li, "li or tab == NULL in get_ants function\n");
	if (!ft_isinteger(line))
		return (FAIL);
	*nb_ants = ft_atoi(line);
	li->flags &= ~FLAG_ANT;
	return (SUCCESS);
}

int	parsing(t_li *li)
{
	char	*line;
	int		nb_ants;
	t_room	*last;

	line = NULL;
	if ((last = malloc(sizeof(t_room))) == NULL)
		return (ERROR);
	li->flags |= FLAG_ANT;
	while (li->flags & FLAG_ANT && get_next_line(0, &line))
	{
		get_ants(li, line, &nb_ants);
		ft_memdel((void **)&line);
	}
	ft_printf("nb_ants = %d\n", nb_ants);
	li->flags |= FLAG_ROOM;
	while (li->flags & FLAG_ROOM && get_next_line(0, &line))
	{
		//ft_printf("%s\n", line);
		get_rooms(li, line, last);
		ft_memdel((void **)&line);
	}
	li->start->next = li->room;
	li->room = li->start;
	room_add(&(li->end), last);
	//ft_printf("last name = %s\n", last->name);
	ft_printf("start name = %s\n", li->start->name);
	while (li->start)
	{
		ft_printf("name = %s\n", li->start->name);
		li->start = li->start->next;
	}
	return (SUCCESS);
}
