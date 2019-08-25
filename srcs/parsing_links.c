/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_links.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:29:05 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/25 14:44:58 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_link(t_li *li, char **line)
{
	if (!line || !*line)
		trigger_error(li, "Bad line\n");
	if (*line[0] == '#')
		return (FAIL);
	if (ft_nb_str_tab(line) != 2)
	{
		li->flags & FLAG_LINK ? trigger_error(li, "Nb args #link\n") : 0;
		return (FAIL);
	}
	return (SUCCESS);
}

int		find_rooms(t_li *li, char *a, char *b)
{
	t_room	*room[2];
	bool	found[2];

	found[0] = false;
	found[1] = false;
	room[0] = NULL;
	room[1] = NULL;
	li->rooms->current = li->rooms->start;
	while (li->rooms->current && (!found[0] || !found[1]))
	{
		if (!found[0] && ft_strequ(a, li->rooms->current->name))
		{
			room[0] = li->rooms->current;
			found[0] = true;
		}
		else if (!found[1] && ft_strequ(b, li->rooms->current->name))
		{
			room[1] = li->rooms->current;
			found[1] = true;
		}
		li->rooms->current = li->rooms->current->next;
	}
	li->rooms->current = li->rooms->start;
	link_new(li, room[0], room[1]);
	return (SUCCESS);
}

int		get_link(t_li *li, char *line)
{
	char	**tab;

	if (!li->rooms->current)
		trigger_error(li, "No room #parsing_links\n");
	tab = ft_strsplit(line, '-');
	if (is_link(li, tab) == FAIL)
	{
		ft_free_tab(&tab);
		return (FAIL);
	}
	find_rooms(li, tab[0], tab[1]);
	ft_free_tab(&tab);
	return (SUCCESS);
}
