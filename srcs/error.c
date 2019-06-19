/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 23:14:25 by sregnard          #+#    #+#             */
/*   Updated: 2019/06/19 13:31:27 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		trigger_error(t_li *li, char *error)
{
	if (!error || !DEBUG)
		error = ERR_DEFAULT;
	write(2, error, ft_strlen(error));
	free_all(li);
	exit(EXIT_FAILURE);
}

