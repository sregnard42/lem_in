/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 21:02:38 by chrhuang          #+#    #+#             */
/*   Updated: 2019/07/31 16:08:10 by chrhuang         ###   ########.fr       */
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
	struct s_path		*next;
}						t_path;

typedef struct			s_list_path
{
	t_path				*start;
	t_path				*current;
	t_path				*end;
	int					size;
}						t_list_path;

#endif
