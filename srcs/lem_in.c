/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:53:46 by sregnard          #+#    #+#             */
/*   Updated: 2019/09/02 11:38:29 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			li_buffer(t_li *li, const char *s, size_t len)
{
	size_t	i;

	i = 0;
	if (li->index + len >= PF_BUFF_SIZE)
	{
		write(1, li->buf, li->index);
		ft_bzero(li->buf, PF_BUFF_SIZE);
		li->index = 0;
	}
	while (i < len && i < LI_BUFF_SIZE)
		li->buf[li->index++] = *(s + i++);
	if (i < len)
		li_buffer(li, s + i, len - i);
	return (SUCCESS);
}

static int	init_li(t_li *li)
{
	li->rooms = ft_memalloc(sizeof(t_list_room));
	li->queue = ft_memalloc(sizeof(t_queue));
	li->queue_res = ft_memalloc(sizeof(t_queue));
	li->paths = ft_memalloc(sizeof(t_list_path));
	li->paths_all = ft_memalloc(sizeof(t_list_path));
	if (!li->rooms || !li->queue || !li->queue_res ||
		!li->paths || !li->paths_all)
		trigger_error(li, "init_li malloc fail\n");
	return (SUCCESS);
}

int	repartition_lists(t_li *li, t_list_path** lists)
{
	int			i;

	i = 0;
	while (lists[++i])
		if (repartition(li, lists[i]) == FAILURE)
			trigger_error(li, "Repartition : FAILURE\n");
		else
			if (!lists[0] || lists[0]->turns > lists[i]->turns)
				lists[0] = lists[i];
	return (SUCCESS);
}

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

static int	options(t_li *li, int ac, char **av)
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

void		print_solution(t_li *li, t_list_path *paths)
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

int			main(int ac, char **av)
{
	t_li	li;

	ft_bzero(&li, sizeof(t_li));
	if (options(&li, --ac, ++av) == ERROR)
		return (ERROR);
	if (li.flags & FLAG_HELP)
		return (print_usage());
	init_li(&li);
	if (parsing(&li) != SUCCESS)
		return (ERROR);
	ft_putendl(li.buf);
	ants_init(&li);
	tree(&li);
	paths_opti_init(&li);
	path_init(&li);
	repartition(&li, li.paths);
	repartition_lists(&li, li.paths_opti);
	ants_set_stage(&li);
	ants_move(&li);
	li.flags & FLAG_SOLUTION ? print_solution(&li, li.paths_opti[0]) : 0;
	free_all(&li);
	return (SUCCESS);
}
