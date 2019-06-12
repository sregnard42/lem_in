/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 12:46:43 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/12 16:25:44 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		link_add(t_room *src, t_room *dst)
{
		t_link	*link;

		if (!(link = (t_link *)malloc(sizeof(t_link))))
				return (FAIL);
		link->dst = dst;
		link->next = NULL;
		++src->nb_links;
		if (!src->links_start)
		{
				src->links_start = link;
				src->links = link;
				src->links_last = link;
				return (SUCCESS);
		}
		src->links_last->next = link;
		src->links_last = link;
		return (SUCCESS);
}

int				link_new(t_room *a, t_room *b)
{
		if (!(a && b))
				ft_putendl("a || b NULL");
		if (link_add(a, b) == FAIL)
				return (FAIL);
		if (link_add(b, a) == FAIL)
				return (FAIL);
		return (SUCCESS);
}
