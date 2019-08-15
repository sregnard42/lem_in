/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:00:19 by sregnard          #+#    #+#             */
/*   Updated: 2019/08/15 13:58:16 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdbool.h>
# include "libft.h"
# include "room.h"
# include "ant.h"
# include "path.h"
# include "link.h"
# include "queue.h"
# include "relative.h"

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
	int					nb_ants;
	t_ant				*ants;
	t_list_room			*rooms;
	t_list_path			*paths;
	t_list_path			*paths_all;
	t_list_path			**paths_opti;
	t_queue				*queue;
	t_queue				*queue_res;
	int					max_path;
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
	FLAG_SP			= (1 << 6),
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
void					room_clean(t_li *li);
void					room_print(t_room *room);
void					room_print_all(t_li *li);

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
t_path					*path_new(t_li *li);
t_path					*path_dup(t_path *path);
int						path_cmp(t_path *path_a, t_path *path_b);
int						path_clear(t_path *path);
void					path_print(t_path *path);
void					path_print_all(t_list_path *pas);

/*
**						path_list.c
*/

void					path_delete(t_list_path *paths, t_path **path_ptr);
t_list_path				*path_list_dup(t_list_path *paths);

/*
**						bfs.c
*/

int						bfs(t_li *li);

/*
**						queue.c
*/

int						queue_print(t_queue *queue);
int						enqueue(t_li *li, t_queue *queue, t_room *room);
int						dequeue(t_queue *queue);
int						clear_queue(t_queue *queue);

/*
**						print_lem_in.c
*/

void					print_lem_in(t_li *li);

/*
**						relative.c
*/

int						relative_add(t_list_relative **list, t_room *room);
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

/*
**						shortest_path.c
*/

int						paths_opti_init(t_li *li);
int						paths_opti(t_li *li);
int						longest_path(t_list_path *paths);
void					print_paths_opti(t_li *li);

/*
**						repartition.c
*/

int						repartition(t_li *li, t_list_path *paths);

/*
**						ant.c
*/

int						ants_init(t_li *li);
void					ants_set_stage(t_li *li);
void					ants_move(t_li *li);

#endif
