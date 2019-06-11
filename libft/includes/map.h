/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 08:26:07 by sregnard          #+#    #+#             */
/*   Updated: 2018/12/26 22:09:42 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "libft.h"

typedef struct	s_map
{
	char		**data;
	int			width;
	int			height;
}				t_map;

t_map			*ft_mapnew(int width, int height, char c);
t_map			*ft_mapfrom(char **data);
void			ft_mapfree(t_map **map);

#endif
