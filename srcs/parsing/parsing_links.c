/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_links.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:29:05 by sregnard          #+#    #+#             */
/*   Updated: 2019/09/08 15:23:38 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool	**matrice_new(t_li *li, int nb)
{
	bool	**matrice;
	int		i;

	i = -1;
	if (!(matrice = (bool **)ft_memalloc(sizeof(bool*) * nb)))
		trigger_error(li, "Error malloc matrice\n");
	while (++i < nb)
		if (!(matrice[i] = (bool *)ft_memalloc(sizeof(bool) * nb)))
			trigger_error(li, "Error malloc matrice\n");
	return (matrice);
}

int		is_link(t_li *li)
{
	if (!li->line_split || !*li->line_split)
		trigger_error(li, "Bad line | is_link\n");
	if (ft_nb_str_tab(li->line_split) != 2)
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

int		get_link(t_li *li)
{
	if (!li->rooms->current)
		trigger_error(li, "No room #parsing_links\n");
	if (ft_strequ(li->line, START) || ft_strequ(li->line, END))
		trigger_error(li, "##start or ##end not followed by room.\n");
	if (*li->line == '#')
		return (FAIL);
	if (ft_strchr(li->line, ' '))
		trigger_error(li, "Space in link.\n");
	li->line_split = ft_strsplit(li->line, '-');
	if (is_link(li) == FAIL)
	{
		ft_free_tab(&li->line_split);
		return (FAIL);
	}
	find_rooms(li, li->line_split[0], li->line_split[1]);
	ft_free_tab(&li->line_split);
	return (SUCCESS);
}
