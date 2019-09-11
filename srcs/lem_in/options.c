/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 15:12:37 by chrhuang          #+#    #+#             */
/*   Updated: 2019/09/11 15:28:24 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	activate_options(t_li *li, char *str)
{
	while (*str)
	{
		if (*str == 't')
			li->flags |= FLAG_TURN;
		else if (*str == 'c')
			li->flags |= FLAG_COLOR;
		else if (*str == 'h')
			li->flags |= FLAG_HELP;
		else if (*str == 'p')
			li->flags |= FLAG_SOLUTION;
		else if (*str == 'd')
			li->flags |= FLAG_DEBUG;
		else
		{
			print_usage();
			return (ERROR);
		}
		++str;
	}
	return (SUCCESS);
}

int			options(t_li *li, int ac, char **av)
{
	int	i;

	i = -1;
	if (!ac)
		return (SUCCESS);
	while (++i < ac)
	{
		if (av[i][0] != '-')
			return (print_usage());
		else
		{
			if (activate_options(li, ++av[i]) == ERROR)
				return (ERROR);
		}
	}
	return (SUCCESS);
}
