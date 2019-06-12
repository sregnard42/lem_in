/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:00:19 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/12 12:38:40 by sregnard         ###   ########.fr       */
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

typedef struct			s_ants
{
		int				id;
		bool			moved;
		struct s_ants	*next;
}						t_ants;

typedef struct			s_links
{
		struct s_rooms	*dst;
		struct s_links	*next;
}						t_links;


typedef struct			s_rooms
{
		char			*name;
		t_point			pos;
		t_links			*links_start;
		t_links			*links;
		t_links			*links_last;
		t_ants			*ants_start;
		t_ants			*ants;
		t_ants			*ants_last;
		int				nb_links;
		int				nb_ants;
		struct s_rooms	*next;

}						t_rooms;

typedef struct			s_li
{
		t_rooms			*start;
		t_rooms			*room;
		t_rooms			*end;
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

int			parsing(t_li *li);
int			get_rooms(t_li *li, char **tab);


/*
**		error.c
*/

void		trigger_error(t_li *li, char *error);

/*
**		room.c
*/

t_rooms		*room_new(char *name, t_point *pos);
void		room_free(t_rooms **ptr);
void		room_print(t_rooms *room);

/*
**		links.c
*/

t_links	*link_add(t_rooms *a, t_rooms *b);
void	link_free(t_links **ptr);
void	link_print(t_links *link);		

/*
**		ant.c
*/

t_ant	*ants_init(int nb_ants);
void	ant_free(t_ants **ptr);
void	ant_print(t_ants *ant);

#endif
