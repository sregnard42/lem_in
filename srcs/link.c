/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 12:46:43 by sregnard          #+#    #+#             */
/*   Updated: 2019/09/08 14:50:40 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				link_clean(t_li *li, t_link *link)
{
	li += 0;
	while (link)
	{
	//	link->dst != li->rooms->end ? link->flags &= ~FLAG_USED : 0;
		link = link->next;
	}
	return (SUCCESS);
}

static int		link_add(t_li *li, t_room *src, t_room *dst)
{
	t_link	*link;

	if (dst == li->rooms->start || src == li->rooms->end)
		return (SUCCESS);
	li += 0;
	if (!(link = (t_link *)ft_memalloc(sizeof(t_link))))
		return (FAIL);
	link->dst = dst;
	link->next = NULL;
	++src->links->size;
	link->flags = 0;
	if (!src->links->first)
	{
		src->links->first = link;
		src->links->current = link;
		src->links->last = link;
		return (SUCCESS);
	}
	src->links->last->next = link;
	src->links->last = link;
	return (SUCCESS);
}

int				link_new(t_li *li, t_room *a, t_room *b)
{
	if (!a)
		return (FAIL);
	if (!b)
		return (FAIL);
	if (li->matrice[a->id][b->id] == true)
		return (SUCCESS);
	li->matrice[a->id][b->id] = true;
	li->matrice[b->id][a->id] = true;
	if (link_add(li, a, b) == FAIL)
		return (FAIL);
	if (link_add(li, b, a) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

void			link_print(t_link *link)
{
	//link->flags & FLAG_CLOSED ? ft_printf("\033[1;31mCLOSED\033[0m ")
	//: ft_printf("\033[1;32mOPENED\033[0m ");
	ft_printf("-> %s\n", link->dst->name);
}
