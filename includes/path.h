/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 21:02:38 by chrhuang          #+#    #+#             */
/*   Updated: 2019/08/27 11:45:02 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include "lem_in.h"

/*
**		PATHS
*/

typedef struct			s_stage
{
	t_room				*room;
	int					turn;
	struct s_stage		*next;
}						t_stage;

typedef struct			s_path
{
	t_stage				*start;
	t_stage				*current;
	t_stage				*end;
	int					size;
	int					capacity;
	int					ant;
	struct s_path		*next;
	struct s_path		*prev;
}						t_path;

typedef struct			s_list_path
{
	t_path				*first;
	t_path				*current;
	t_path				*last;
	t_path				*longest_path;
	int					sum;
	int					turns;
	int					size;
	t_ant				*ant;
}						t_list_path;

#endif
