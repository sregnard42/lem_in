/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:22:20 by chrhuang          #+#    #+#             */
/*   Updated: 2019/06/12 13:37:19 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

static int	get_ants(t_li *li, char *line, t_ant **ant_start)
{
	if (li == NULL || line == NULL)
		trigger_error(li, "li or tab == NULL in get_ants function\n");
	if (!ft_isinteger(line))
		return (FAIL);
	*ant_start = ants_init(ft_atoi(line));
	li->flags &= ~FLAG_ANT;
	return (SUCCESS);
}

int	parsing(t_li *li)
{
	char	*line;
	t_ant	*start;

	line = NULL;
	//li->flags |= FLAG_ANT;
	while (li->flags & FLAG_ANT && get_next_line(0, &line))
	{
		li->flags & FLAG_ANT ? 0 : get_ants(li, line, &start);
		ft_memdel((void **)line);
	}
	li->flags |= FLAG_ROOM;
	while (get_next_line(0, &line) && li->flags & FLAG_ROOM)
	{
		ft_printf("%s\n", line);
		//get_rooms(li, line);
		ft_memdel((void **)line);
	}
	return (SUCCESS);
}
