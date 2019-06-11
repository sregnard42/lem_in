/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:00:19 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/11 15:12:18 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H


# include "libft.h"

# define DEBUG			1
# define ERR_DEFAULT	"Error\n"

# define START			"##start"
# define END			"##end"

typedef struct	s_lem_in
{
		t_list	*rooms;
		t_list	*links;
		t_list	*ants; //tmp
		t_room	*start;
		t_room	*end;
		int		ants_moving;
}				t_li;

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
