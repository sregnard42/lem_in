/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:50:26 by sregnard          #+#    #+#             */
/*   Updated: 2018/12/17 14:02:14 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "libft.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;

void				ft_lstadd(t_list **alst, t_list *new);
t_list				*ft_lstcpy(t_list *src);
void				ft_lstdel(t_list **alst, void (*del)(void **, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void **, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
int					ft_lstlen(t_list **alst);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void *content, size_t content_size);

#endif
