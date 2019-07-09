/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:47:11 by sregnard          #+#    #+#             */
/*   Updated: 2019/07/09 12:49:23 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARENT_H
# define PARENT_H

# include "lem_in.h"

/*
**		PARENT
*/

typedef struct			s_parent
{
	t_room				*room;
	struct s_parent		*next;
}						t_parent;

typedef struct			s_list_parent
{
	t_parent			*first;
	t_parent			*current;
	t_parent			*last;
	int					size;
}						t_list_parent;

#endif
