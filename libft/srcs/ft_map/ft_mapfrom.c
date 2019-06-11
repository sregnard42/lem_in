/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapfrom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 22:05:29 by sregnard          #+#    #+#             */
/*   Updated: 2018/12/27 10:24:44 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_map	*ft_mapfrom(char **data)
{
	t_map	*map;

	if (!data || !*data)
		return (NULL);
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	map->data = data;
	map->height = ft_nb_str_tab(data);
	map->width = ft_strlen(*data);
	return (map);
}
