/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:47:11 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/21 13:54:46 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RELATIVE_H
# define RELATIVE_H

# include "lem_in.h"

/*
**		RELATIVE (CHILD || PARENT)
*/

typedef struct			s_relative
{
	t_room				*room;
	struct s_relative	*next;
}						t_relative;

typedef struct			s_list_relative
{
	t_relative			*first;
	t_relative			*current;
	t_relative			*last;
	int					size;
}						t_list_relative;

#endif
