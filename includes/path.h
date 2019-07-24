/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 21:02:38 by chrhuang          #+#    #+#             */
/*   Updated: 2019/07/24 10:51:58 by chrhuang         ###   ########.fr       */
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
}						t_path;

#endif
