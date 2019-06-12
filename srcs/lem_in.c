/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:53:46 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/12 11:49:15 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			main(int ac, char **av)
{
		t_li	li;

		ft_bzero(&li, sizeof(t_li));
		if (--ac == 0)
			trigger_error(&li, "No argument\n");
		if (parsing(ac, ++av, &li) != SUCCESS)
			return (ERROR);
		return (SUCCESS);
}
