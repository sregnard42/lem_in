/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:00:19 by sregnard          #+#    #+#             */
/*   Updated: 2019/09/11 10:48:57 by sregnard         ###   ########.fr       */
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

# define LI_BUFF_SIZE	1000000

# define CYAN			"\033[1;36m"
# define GREEN			"\033[1;32m"
# define YELLOW			"\033[1;33m"
# define RED			"\033[1;31m"
# define RESET			"\033[0m"

/*
**		LEM-IN
*/

typedef struct			s_li
{
	char				buf[LI_BUFF_SIZE];
	unsigned int		index;
	char				*line;
	char				**line_split;
	bool				**links;
	int					max_path;
	int					nb_ants;
	t_ant				*ants;
	t_list_room			*rooms;
	t_room				*start;
	t_room				*end;
	t_queue				*queue;
	t_queue				*queue_res;
	t_list_path			*paths;
	t_list_path			*paths_all;
	t_list_path			**paths_opti;
	unsigned int		flags;
}						t_li;

enum					e_flags_li
{
	FLAG_START = (1 << 0),
	FLAG_END = (1 << 1),
	FLAG_ANT = (1 << 2),
	FLAG_ROOM = (1 << 3),
	FLAG_LINK = (1 << 4),
	FLAG_DIRECT = (1 << 5),
	FLAG_SP = (1 << 6),
	FLAG_HELP = (1 << 7),
	FLAG_TURN = (1 << 8),
	FLAG_COLOR = (1 << 9),
	FLAG_SOLUTION = (1 << 10),
};

/*
**						Lem-in
*/

int						li_buffer(t_li *li, const char *s, size_t len);

/*
**						Errors
*/

void					trigger_error(t_li *li, char *error);

/*
**						Options
*/

int						options(t_li *li, int ac, char **av);
int						print_usage(void);
void					print_solution(t_li *li, t_list_path *paths);
void					print_turn(t_li *li);
void					print_path(t_path *path);

/*
**						Parsing
*/

int						parsing(t_li *li);
int						get_room(t_li *li);
int						get_link(t_li *li);
int						is_link(t_li *li);
bool					**matrice_new(t_li *li, int nb);

/*
**						Ants
*/

int						ants_init(t_li *li);
void					ants_set_stage(t_li *li);
void					ants_move(t_li *li);

/*
**						Rooms
*/

t_room					*room_new(t_li *li, char *name, t_point *pos);
void					room_add(t_li *li, t_room *new_room);
void					room_clean(t_li *li);
int						already_exists(t_li *li, char *name, t_point *pos);

/*
** 						Matrice
*/

/*
**						Links
*/

int						link_new(t_li *li, t_room *a, t_room *b);
int						link_clean(t_li *li, t_link *link);

/*
**						BFS
*/

int						bfs(t_li *li);
int						tree(t_li *li);
int						enqueue(t_li *li, t_queue *queue, t_room *room);
int						dequeue(t_queue *queue);
int						clear_queue(t_queue *queue);

/*
**						Relatives
*/

int						relative_add(t_list_relative **list, t_room *room);
int						parent_of(t_room *room, t_room *child);

/*
**						Paths
*/

int						path_init(t_li *li);
t_path					*path_new(t_li *li);
t_path					*path_dup(t_path *path);
int						path_clear(t_path *path);

int						path_cmp(t_path *path_a, t_path *path_b);
int						path_already_found(t_list_path *paths, t_path *path);
int						path_collision(t_li *li, t_path *path);

int						path_add(t_list_path *paths, t_path *path);
t_list_path				*path_list_dup(t_li *li, t_list_path *paths);
void					path_delete(t_list_path *paths, t_path **path_ptr);

int						paths_opti_init(t_li *li);
int						paths_opti(t_li *li);

/*
**						Repartition
*/

int						repartition(t_li *li, t_list_path *paths);
int						repartition_lists(t_li *li, t_list_path **lists);

/*
**						Free
*/

int						free_all(t_li *li);
void					free_path(t_path **path_ptr);
void					free_paths(t_list_path **paths_ptr);
void					free_paths_list(t_list_path **lists);
void					free_rooms(t_li *li);

#endif
