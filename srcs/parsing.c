/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:22:20 by chrhuang          #+#    #+#             */
/*   Updated: 2019/09/02 23:00:11 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

static int	get_ants(t_li *li, char *line, int *nb_ants)
{
	if (li == NULL || line == NULL)
		trigger_error(li, "li or tab == NULL in get_ants function\n");
	if (ft_strequ(line, START) || ft_strequ(line, END))
		trigger_error(li, "##start or ##end instead of nb ants.\n");
	if (*line == '#')
		return (FAIL);
	if (!ft_isinteger(line))
		trigger_error(li, "not integer #ant\n");
	if ((*nb_ants = ft_atoi(line)) <= 0)
		trigger_error(li, "ant <= 0 #ant\n");
	li->flags &= ~FLAG_ANT;
	li->flags |= FLAG_ROOM;
	return (SUCCESS);
}

static void	parsing_room_link(t_li *li, char *line)
{
	t_room	*last;

	last = NULL;
	while (get_next_line(0, &line))
	{
		li->flags & FLAG_ROOM ? get_room(li, line, &last) : 0;
		li->flags & FLAG_LINK ? get_link(li, line) : 0;
		line = ft_stradd(line, "\n");
		li_buffer(li, line, ft_strlen(line));
		ft_memdel((void **)&line);
	}
}

int			parsing(t_li *li)
{
	int		nb_ants;

	li->flags |= FLAG_ANT;
	while (li->flags & FLAG_ANT && get_next_line(0, &li->line))
	{
		get_ants(li, li->line, &nb_ants);
		li->line = ft_stradd(li->line, "\n");
		li_buffer(li, li->line, ft_strlen(li->line));
		ft_memdel((void **)&li->line);
	}
	parsing_room_link(li, li->line);
	li->nb_ants = nb_ants;
	li->rooms->current = li->rooms->start;
	if (!li->rooms->start)
		trigger_error(li, "rooms->start == NULL\n");
	li->rooms->start->prev = NULL;
	return (SUCCESS);
}
