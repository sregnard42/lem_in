/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 23:14:25 by sregnard          #+#    #+#             */
/*   Updated: 2019/09/11 15:32:53 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		trigger_error(t_li *li, char *error)
{
	if (!error || (!DEBUG && !(li->flags & FLAG_DEBUG)))
		error = ERR_DEFAULT;
	else
		write(2, "ERROR: ", 7);
	write(2, error, ft_strlen(error));
	free_all(li);
	exit(EXIT_FAILURE);
}
