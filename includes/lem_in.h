/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:00:19 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/12 12:23:05 by sregnard         ###   ########.fr       */
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

typedef struct			s_room
{
		char			*name;
		t_point			pos;
		t_link			*links;
		t_ant			*ants;
		int				nb_links;
		int				nb_ants;
		struct s_room	*next;

}						t_room;

typedef struct			s_links
{
		t_room			*dst;
		struct s_link	*next;
}						t_links;


typedef struct			s_ant
{
		int				id;
		bool			moved;
		struct s_ant	*next;
}						t_ant;

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
};

/*
**		Parsing
*/

int			parsing(int ac, char **av, t_li *li);
int			get_rooms(t_li *li, char **tab);


/*
**		error.c
*/

void		trigger_error(t_li *li, char *error);

/*
**		room.c
*/

t_room		*room_new(char *name, t_point *pos);
void		room_free(void **ptr, size_t size);
void		room_print(t_room *room);

/*
**		links.c
*/

t_link	*links_new(t_room *room1, t_room *room2);
void	link_free(void **ptr, size_t size);
void	link_print(t_link *link);		

/*
**		ant.c
*/

t_ant	*ants_init(int nb_ants);
void	ant_free(void **ptr, size_t size);
void	ant_print(t_ant *ant);

#endif
