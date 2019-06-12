/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_links.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:29:05 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/12 18:11:49 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_link(char **line)
{
		if (!line)
				return (FAIL);
		if (*line[0] == '#')
				return (FAIL);
		if (ft_nb_str_tab(line) != 2)
				return (FAIL);
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

		li += 0;
		tab = ft_strsplit(line, '-');
		if (is_link(tab) == FAIL)
		{
				ft_free_tab(&tab);
				return (FAIL);
		}
		a = NULL;
		b = NULL;
		find_rooms(li, tab[0], tab[1], &a, &b);
		if (!(a && b))
				trigger_error(li, "a || b NULL\n");
		link_new(a, b);
		ft_free_tab(&tab);
		return (SUCCESS);
}
