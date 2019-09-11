/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 21:00:58 by chrhuang          #+#    #+#             */
/*   Updated: 2019/09/11 09:53:57 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINK_H
# define LINK_H

# include "lem_in.h"

/*
**		LINKS
*/

typedef struct			s_link
{
	t_room				*dst;
	unsigned int		flags;
	struct s_link		*next;
}						t_link;

typedef struct			s_list_link
{
	t_link				*first;
	t_link				*current;
	t_link				*last;
	int					size;
}						t_list_link;

enum					e_flags_link
{
	FLAG_CLOSED = (1 << 0),
};

#endif
