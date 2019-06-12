/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 12:46:43 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/12 13:19:25 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		link_add(t_room *src, t_room *dst)
{
		t_link	*link;

		if (!(link = (t_link *)malloc(sizeof(t_link))))
				return (FAILURE);
		link->dst = dst;
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
		if (link_add(a, b) == FAILURE)
				return (FAILURE);
		if (link_add(b, a) == FAILURE)
				return (FAILURE);
		return (SUCCESS);
}
