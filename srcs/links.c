/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:53:47 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/12 12:40:03 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		*link_add(t_room *a, t_room *b)
{
		t_links	*a_link;
		t_links	*b_link;

		if (!(a_link = (t_links *)malloc(sizeof(t_links))))
				return (FAILURE);
		if (!(b_link = (t_links *)malloc(sizeof(t_links))))
				return (FAILURE);
		return (SUCCESS);
}

void	link_free(void **ptr)
{
		t_link	*link;

		ft_printf("Freeing link. Starting\n");
		link = (t_link *)*ptr;
		ft_lstdel(&(link->rooms), &room_free);
		ft_bzero(*ptr, size);
		ft_memdel(ptr);
		ft_printf("Freeing link. Done.\n");
}

void	link_print(t_links *link)
{
		ft_printf("LINK_PRINT\n");
		room_print(link->rooms->content);
		room_print(link->rooms->next->content);
		ft_printf("/LINK_PRINT\n\n");
}
