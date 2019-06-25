/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:00:19 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/25 15:56:38 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdbool.h>

# define DEBUG			0
# define ERR_DEFAULT	"ERROR\n"

# define ERROR			-1
# define FAIL			0
# define FAILURE		0
# define SUCCESS		1

# define START			"##start"
# define END			"##end"

# define LI_BUFF_SIZE	4096

/*
**		ROOMS
*/

typedef struct			s_room
{
	char				*name;
	t_point				pos;
	struct s_list_link	*links;
	struct s_room		*parent;
	struct s_room		*next;
	struct s_room		*prev;
	unsigned int		flags;
}						t_room;

typedef struct			s_list_room
{
	t_room				*start;
	t_room				*current;
	t_room				*end;
	int					size;
}						t_list_room;

enum					e_flags_room
{
	FLAG_VISITED = (1 << 0),
	FLAG_RESERVED = (2 << 0),
	FLAG_QUEUED = (3 << 0),
};

/*
**		LINKS
*/

typedef struct			s_link
{
	t_room				*dst;
	unsigned int		flags;
	struct s_link		*next;
}						t_link;

typedef struct			s_list_link
{
	t_link				*first;
	t_link				*current;
	t_link				*last;
	int					size;
}						t_list_link;

enum					e_flags_link
{
	FLAG_USED = (1 << 0),
};

/*
**		PATHS
*/

typedef struct			s_path
{
	t_room				*room;
	int					round;
	struct s_path		*next;
}						t_path;

typedef struct			s_list_path
{
	t_path				*start;
	t_path				*current;
	t_path				*end;
	int					size;
}						t_list_path;

/*
**		ANTS
*/

typedef struct			s_ant
{
	int					id;
	bool				moved;
	t_room				*room;
	t_list_path			*path;
	struct s_ant		*next;
}						t_ant;

typedef struct			s_list_ant
{
	t_ant				*first;
	t_ant				*current;
	t_ant				*last;
	int					size;
}						t_list_ant;

/*
**		QUEUE
*/

typedef struct			s_queue
{
	t_room				*room;
	struct s_queue		*next;
}						t_queue;

typedef struct			s_list_queue
{
	t_queue				*first;
	t_queue				*current;
	t_queue				*last;
}						t_list_queue;

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
void					room_free(t_room **ptr);
void					room_print(t_room *room);
void					room_clean(t_li *li, t_room *room);

/*
**						links.c
*/

int						link_new(t_li *li, t_room *a, t_room *b);
void					link_free(t_link **ptr);
void					link_print(t_link *link);
void					link_clean(t_li *li, t_link *link);

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
void					ant_free(t_ant **ptr);
void					ant_print(t_ant *ant);
void					ant_print_all(t_li *li);

/*
**						move_ant.c
*/

int						move_ant(t_ant *ant, t_room *dst);

/*
**						bfs.c
*/

int						bfs(t_li *li, int turn);

#endif
