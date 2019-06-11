/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 14:18:30 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/11 19:22:08 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

# include <stdlib.h>

typedef struct	s_point
{
	int	x;
	int	y;
	int	z;
}				t_point;

t_point			*ft_ptnew(int x, int y, int z);
void			ft_ptcpy(t_point *dst, t_point *src);
void			ft_ptset(t_point *pt, int x, int y, int z);
void			ft_ptprint(t_point *pt);
void			ft_ptfree(void **pt, size_t size);

#endif
