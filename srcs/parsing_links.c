/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_links.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:29:05 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/19 13:32:12 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_link(t_li *li, char **line)
{
	li += 0;
	if (!line)
		return (FAIL);
	if (*line[0] == '#')
		return (FAIL);
	if (ft_nb_str_tab(line) != 2)
	{
		li->flags & FLAG_LINK ? trigger_error(li, "Nb args #link\n") : 0;
		return (FAIL);
	}
	return (SUCCESS);
}

int		find_rooms(t_li *li, char *a, char *b, t_room **ra, t_room **rb)
{
	t_room	*tmp;
	bool	fa;
	bool	fb;

	fa = false;
	fb = false;
	tmp = li->start;
	while (tmp)
	{
		if (!fa && ft_strequ(a, tmp->name))
		{
			*ra = tmp;
			fa = true;
		}
		else if (!fb && ft_strequ(b, tmp->name))
		{
			*rb = tmp;
			fb = true;
		}
		tmp = tmp->next;
	}
	if (!(a &&b))
		return (FAIL);
	return (SUCCESS);
}

int		get_link(t_li *li, char *line)
{
	char	**tab;
	t_room	*a;
	t_room	*b;

	if (!li->room)
		trigger_error(li, "No room\n");
	tab = ft_strsplit(line, '-');
	if (is_link(li, tab) == FAIL)
	{
		ft_free_tab(&tab);
		return (FAIL);
	}
	a = NULL;
	b = NULL;
	find_rooms(li, tab[0], tab[1], &a, &b);
	if (!(a && b))
		trigger_error(li, "Room name not found\n");
	link_new(li, a, b);
	ft_free_tab(&tab);
	return (SUCCESS);
}
