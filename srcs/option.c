/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 15:12:37 by chrhuang          #+#    #+#             */
/*   Updated: 2019/09/07 15:26:23 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		print_usage(void)
{
	ft_printf("%-8s:   %s\n%-8s:   %s\n%s\n",
	"Usage",
	"./lem_in [options < map]",
	"Options",
	"-t -> show turn",
	"            -c -> color");
	return (ERROR);
}

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
		else
		{
			print_usage();
			return (ERROR);
		}
		++str;
	}
	return (SUCCESS);
}

int		options(t_li *li, int ac, char **av)
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
			if (activate_options(li, ++av[i]) == ERROR)
				return (ERROR);
	}
	return (SUCCESS);
}

void	print_solution(t_li *li, t_list_path *paths)
{
	int	color;
	int	i;

	color = 32;
	paths->current = paths->first;
	i = 0;
	li->flags & FLAG_COLOR ? ft_printf("%s", CYAN) : 0;
	ft_printf("\nSolution :%s\n", RESET);
	li->flags & FLAG_COLOR ? 0 : (color = 0);
	while (paths->current)
	{
		ft_printf("%s", li->flags & FLAG_COLOR ? CYAN : RESET);
		ft_printf("[ %d ] %s", ++i, RESET);
		ft_printf("\033[1;%dm", color);
		path_print(paths->current);
		if (li->flags & FLAG_COLOR)
			color == 36 ? color = 32 : ++color;
		paths->current = paths->current->next;
	}
	ft_printf("%s", RESET);
}