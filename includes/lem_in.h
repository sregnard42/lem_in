/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:00:19 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/11 18:27:10 by sregnard         ###   ########.fr       */
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

typedef struct	s_room
{
		char	*name;
		t_point	pos;
		t_list	*links;
		t_list	*ants;
		int		nb_links;
		int		nb_ants;

}				t_room;

typedef struct	s_link
{
		t_list	*rooms;
}				t_link;


typedef struct	s_ant
{
		int		id;
		bool	moved;
}				t_ant;

typedef struct	s_lem_in
{
		t_list	*rooms;
		t_list	*links;
		t_list	*ants; //tmp
		t_room	*start;
		t_room	*end;
		int		ants_moving;
}				t_li;

/*
**		error.c
*/

void	trigger_error(t_li *li, char *error);

/*
**		room.c
*/

t_room	*room_new(char *name, t_point pos);
void	room_free(void **ptr, size_t size);
void	room_print(t_room *room);		

/*
**		link.c
*/

t_link	*link_new(t_room *room1, t_room *room2);
void	link_free(void **ptr, size_t size);
void	link_print(t_link *link);		

/*
**		ant.c
*/

t_list	*ants_init(int nb_ants);
void	ant_free(void **ptr, size_t size);
void	ant_print(t_ant *ant);

#endif
