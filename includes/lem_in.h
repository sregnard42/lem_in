/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:00:19 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/30 11:38:15 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdbool.h>
# include "libft.h"
# include "room.h"
# include "path.h"
# include "ant.h"
# include "link.h"
# include "booking.h"
# include "queue.h"

# define DEBUG			1
# define ERR_DEFAULT	"ERROR\n"

# define ERROR			-1
# define FAIL			0
# define FAILURE		0
# define SUCCESS		1

# define START			"##start"
# define END			"##end"

# define LI_BUFF_SIZE	4096

/*
**		LEM-IN
*/

typedef struct			s_li
{
	char				buf[LI_BUFF_SIZE];
	unsigned int		index;
	t_list_room			*rooms;
	t_list_ant			*ants;
	t_list_queue		*queue;
	t_booking			*bookings;
	unsigned int		booking_size;
	int					moves;
	unsigned int		flags;
}						t_li;

enum					e_flags_li
{
	FLAG_START = (1 << 0),
	FLAG_END = (1 << 1),
	FLAG_ANT = (1 << 2),
	FLAG_ROOM = (1 << 3),
	FLAG_LINK = (1 << 4),
};

/*
**						lem_in.c
*/

int						free_all(t_li *li);
int						li_buffer(t_li *li, const char *s, size_t len);

/*
**						parsing.c
**						parsing_rooms.c
**						parsing_links.c
*/

int						parsing(t_li *li);
int						get_room(t_li *li, char *line, t_room **last);
int						get_link(t_li *li, char *line);
int						is_link(t_li *li, char **line);

/*
**						error.c
*/

void					trigger_error(t_li *li, char *error);

/*
**						room.c
*/

t_room					*room_new(char *name, t_point *pos);
void					room_add(t_room **rooms, t_room *new_room);
void					room_print(t_room *room);
void					room_clean(t_li *li, t_room *room);

/*
**						links.c
*/

int						link_new(t_li *li, t_room *a, t_room *b);
int						link_clean(t_li *li, t_link *link);
void					link_print(t_link *link);

/*
**						path.c
*/

int						path_init(t_li *li);
int						path_insert(t_ant *ant, t_room *room, int round);
void					path_print(t_path *path);

/*
**						ant.c
*/

int						ants_init(t_li *li, int nb_ants);
int						ant_move(t_ant *ant, t_room *dst);
void					ant_print(t_ant *ant);
void					ant_print_all(t_li *li);

/*
**						booking.c
*/

int						booking_init(t_li *li);

/*
**						bfs.c
*/

int						bfs(t_li *li, int turn);

#endif
