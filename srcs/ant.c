/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:11:11 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/25 22:06:43 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ants_init(t_li *li, int nb_ants)
{
	t_ant	*ant;
	int		i;

	i = 0;
	li->ants->size = nb_ants;
	while (++i <= nb_ants)
	{
		if (!(ant = (t_ant *)malloc(sizeof(t_ant))))
			return (FAIL);
		ft_bzero(ant, sizeof(t_ant));
		ant->id = i;
		ant->room = li->rooms->start;
		if ((ant->path = (t_list_path *)malloc(sizeof(t_list_path))) == NULL)
			trigger_error(li, "ants_init malloc NULL\n");
		ft_bzero(ant->path, sizeof(t_list_path));
		if (i == 1)
		{
			li->ants->first = ant;
			li->ants->current = ant;
			li->ants->last = ant;
		}
		else
		{
			li->ants->last->next = ant;
			li->ants->last = ant;
		}
	}
	return (SUCCESS);
}

void	ant_print(t_ant *ant)
{
	ft_printf("L%d-%s ", ant->id, ant->room->name);
	ant->moved ? 0 : ft_printf("(X) ");
	ant->path->current ? ft_printf("yea\t") : ft_printf("nah\t");
}

void	ant_print_all(t_li *li)
{
	li->ants->current = li->ants->first;
	while (li->ants->current)
	{
		//li->ants->moved ? ant_print(li->ants) : 0;
		ant_print(li->ants->current);
		li->ants->current = li->ants->current->next;
	}
	li->ants->current = li->ants->first;
	ft_putln();
}
