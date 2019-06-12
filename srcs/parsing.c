/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:22:20 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/12 13:20:54 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

static int	get_ants(t_li *li, char *line)
{
	if (li == NULL || line == NULL)
		trigger_error(li, "li or tab == NULL in get_ants function\n");
	if (!ft_isinteger(line))
		return (FAIL);
	ants_init(ft_atoi(line));
	return (SUCCESS);
}

int	parsing(t_li *li)
{
	char	*line;

	line = NULL;
	//tab = tab_start;
	while (get_next_line(0, &line))
	{
		li->flags & FLAG_ANT ? 0 : get_ants(li, line);
		//get_rooms(li, line);
		ft_memdel((void **)line);
	}
	return (SUCCESS);
}
