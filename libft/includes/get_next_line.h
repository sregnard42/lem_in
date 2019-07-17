/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 15:08:48 by sregnard          #+#    #+#             */
/*   Updated: 2019/07/17 14:08:04 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 10000
# define FD_MAX 4864

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

int	get_next_line(int fd, char **line);
int	get_next_line_custom(int fd, char **line);

#endif
