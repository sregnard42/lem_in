/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:53:47 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/11 17:16:08 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_link	*link_new(t_room *room1, t_room *room2)
{
		t_link	*link;
		t_list	*elem1;
		t_list	*elem2;

		if (!(link = (t_link *)malloc(sizeof(t_link))))
				return (NULL);
		ft_bzero(link, sizeof(t_link));
		if (!(elem1 = ft_lstnew(room1, sizeof(t_room))))
				return (NULL);
		if (!(elem2 = ft_lstnew(room2, sizeof(t_room))))
				return (NULL);
		link->rooms = elem1;
		ft_lstadd(&link->rooms, elem2); 
		return (link);
}

void	link_free(void **ptr, size_t size)
{
		t_link	*link;

		ft_printf("Freeing link. Starting\n");
		link = (t_link *)*ptr;
		ft_lstdel(&(link->rooms), &room_free);
		ft_bzero(*ptr, size);
		ft_memdel(ptr);
		ft_printf("Freeing link. Done.\n");
}

void	link_print(t_link *link)
{
		ft_printf("LINK_PRINT\n");
		room_print(link->rooms->content);
		room_print(link->rooms->next->content);
		ft_printf("/LINK_PRINT\n\n");
}
