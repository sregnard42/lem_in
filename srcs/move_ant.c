/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:50:50 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/13 11:50:51 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**          Remove ant from room
*/

static int  del_ant(t_ant *ant, t_room *src)
{
    src->ants_start = ant->next;
    ant->next = NULL;
    if (!src->ants_start)
    {
        src->ants = NULL;
        src->ants_last = NULL;
    }
    else
        src->ants = src->ants_start;
    --src->nb_ants;
    return (SUCCESS);
}

/*
**          Add ant to a room
*/

static int  add_ant(t_ant *ant, t_room *dst)
{
    if (dst->ants_last)
    {
        dst->ants_last->next = ant;
        dst->ants_last = ant;
    }
    else
    {
        dst->ants_start = ant;
        dst->ants = ant;
        dst->ants_last = ant;
    }
    ++dst->nb_ants;
    return (SUCCESS);
}

/*
**          Transfer an ant from one room to another
*/

int         move_ant(t_room *src, t_room *dst)
{
    t_ant   *ant;

    if (!(src && dst))
        return (FAIL);
    ant = src->ants_start;
    if (!ant)
        return (FAIL);
    del_ant(ant, src);
    add_ant(ant, dst);
    ant->moved = 1;
    return (SUCCESS);
}