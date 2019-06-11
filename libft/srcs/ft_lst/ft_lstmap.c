/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:15:22 by sregnard          #+#    #+#             */
/*   Updated: 2018/11/16 09:06:08 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*lst_head;
	t_list	*elem;

	if (!(lst && f && *f))
		return (NULL);
	lst_head = f(lst);
	elem = lst_head;
	lst = lst->next;
	while (lst)
	{
		elem->next = f(lst);
		elem = elem->next;
		lst = lst->next;
	}
	return (lst_head);
}
