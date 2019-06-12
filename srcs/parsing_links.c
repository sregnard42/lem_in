/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_links.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:29:05 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/12 15:45:48 by sregnard         ###   ########.fr       */
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

int		get_link(t_li *li, char *line)
{
		char	**tab;

		li += 0;
		tab = ft_strsplit(line, '-');
		if (is_link(tab) == FAIL)
				return (FAIL);
		return (SUCCESS);
}
