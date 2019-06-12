/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:00:19 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/12 14:49:13 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include <stdbool.h>

# define DEBUG			1
# define ERR_DEFAULT	"Error\n"

# define ERROR			-1
# define FAIL			0
# define SUCCESS		1

# define START			"##start"
# define END			"##end"

typedef struct			s_ant
{
		int				id;
		bool			moved;
		struct s_ant	*next;
}						t_ant;

typedef struct			s_link
{
		struct s_room	*dst;
		struct s_link	*next;
}						t_link;


typedef struct			s_room
{
		char			*name;
		t_point			pos;
		t_link			*links_start;
		t_link			*links;
		t_link			*links_last;
		t_ant			*ants_start;
		t_ant			*ants;
		t_ant			*ants_last;
		int				nb_links;
		int				nb_ants;
		struct s_room	*next;

}						t_room;

typedef struct			s_li
{
		t_room			*start;
		t_room			*room;
		t_room			*end;
		int				moves;
		int				flags;
}						t_li;

enum					e_flags
{
		FLAG_START = (1 << 0),
		FLAG_END = (1 << 1),
		FLAG_ANT = (1 << 2),
		FLAG_ROOM = (1 << 3),
};

/*
**		Parsing
*/

int			parsing(t_li *li);
int			get_rooms(t_li *li, char *line, t_room *last);


/*
**		error.c
*/

void		trigger_error(t_li *li, char *error);

/*
**		room.c
*/

t_room		*room_new(char *name, t_point *pos);
void		room_add(t_room **rooms, t_room *new);
void		room_free(t_room **ptr);
void		room_print(t_room *room);

/*
**		links.c
*/

t_link	*link_add(t_room *a, t_room *b);
void	link_free(t_link **ptr);
void	link_print(t_link *link);		

/*
**		ant.c
*/

int 	ants_init(t_room *r, int nb_ants);
void	ant_free(t_ant **ptr);
void	ant_print(t_ant *ant);

#endif
