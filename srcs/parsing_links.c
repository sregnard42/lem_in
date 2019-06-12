/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_links.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:29:05 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/12 16:03:09 by chrhuang         ###   ########.fr       */
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

	tmp = li->start;
	while (tmp)
	{
		if (ft_strequ(a, tmp->name))
			*ra = tmp;
		else if (ft_strequ(b, tmp->name))
			*rb = tmp;
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int		get_link(t_li *li, char *line)
{
		char	**tab;

		li += 0;
		tab = ft_strsplit(line, '-');
		if (is_link(tab) == FAIL)
				return (FAIL);
		return (SUCCESS);
}
