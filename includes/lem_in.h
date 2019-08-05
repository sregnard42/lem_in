/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:00:19 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/05 19:37:21 by sregnard         ###   ########.fr       */
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
# include "parent.h"

# define DEBUG			1
# define ERR_DEFAULT	"ERROR\n"

# define ERROR			-1
# define FAIL			0
# define FAILURE		0
# define SUCCESS		1

# define START			"##start"
# define END			"##end"

# define LI_BUFF_SIZE	10000

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
	t_list_booking		**bookings;
	t_list_path			*paths;
	int					max_turn;
	int					moves;
	char				**path_mat;
	unsigned int		flags;
	bool				**matrice;
}						t_li;

enum					e_flags_li
{
	FLAG_START		= (1 << 0),
	FLAG_END		= (1 << 1),
	FLAG_ANT		= (1 << 2),
	FLAG_ROOM		= (1 << 3),
	FLAG_LINK		= (1 << 4),
	FLAG_DIRECT		= (1 << 5),
	FLAG_FIRST_TRY	= (1 << 6)
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

t_room					*room_new(t_li *li, char *name, t_point *pos);
void					room_add(t_room **rooms, t_room *new_room);
void					room_clean(t_li *li, t_room *room);
void					room_print(t_room *room);
void					room_print_all(t_room *room);

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
void					path_print(t_stage *path);

/*
**						ant.c
*/

int						ants_init(t_li *li, int nb_ants);
int						ant_move(t_ant *ant, t_room *dst);
void					ant_print(t_ant *ant, t_room *end);
void					ant_print_all(t_li *li);

/*
**						booking.c
*/

int						booking_init(t_li *li);
int						add_booking(t_li *li, t_room *room, int turn);
int						booking_turn(t_li *li, int turn);
void					print_booking(t_li *li);

/*
**						bfs.c
*/

int						bfs(t_li *li, int turn);
int						bfs_maxflow(t_li *li, int turn);

/*
**						queue.c
*/

int						queue_print(t_queue *queue);
int						enqueue(t_li *li, t_room *room, int turn);	
int						dequeue(t_li *li);
int						clear_queue(t_li *li, t_room *room);

/*
**						print_lem_in.c
*/

void					print_lem_in(t_li *li);

/*
**						parent.c
*/

int						parent_add(t_room *child, t_room *room);
int						parent_of(t_room *room, t_room *child);
int						parent_print_all(t_room *room);

/*
**						tree.c
*/

int						tree(t_li *li);

/*
** 						matrice.c
*/

void					print_matrice(bool **matrice, int nb);
void					new_matrice(t_li *li, int nb);

#endif
