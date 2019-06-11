/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 08:12:48 by sregnard          #+#    #+#             */
/*   Updated: 2018/12/13 08:39:53 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	eol_found(const int fd, char *line, char **overflow)
{
	int		i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == EOL)
		{
			line[i] = EOS;
			overflow[fd] = ft_strdup(&line[i + 1]);
			ft_strclr(&line[i + 1]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	err_found(const int fd, char **line, char **overflow)
{
	if (BUFF_SIZE < 1 || fd < 0 || fd > FD_MAX || !line || read(fd, NULL, 0))
		return (1);
	if (overflow[fd])
	{
		*line = ft_strdup(overflow[fd]);
		ft_strclr(overflow[fd]);
		ft_memdel((void **)&overflow[fd]);
		if (!(*line))
			return (1);
	}
	else
		*line = NULL;
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	overflow[FD_MAX + 1][BUFF_SIZE + 1];
	int			bytes_read;
	int			found_eol;

	if (err_found(fd, line, (char **)overflow))
		return (-1);
	if ((found_eol = eol_found(fd, *line, (char **)overflow)))
		return (1);
	while (!found_eol && (bytes_read = read(fd, overflow[fd], BUFF_SIZE)))
	{
		overflow[fd][bytes_read] = EOS;
		*line = ft_stradd(*line, overflow[fd]);
		found_eol = eol_found(fd, *line, (char **)overflow);
	}
	if (found_eol || (!bytes_read && ft_strlen(*line)))
		return (1);
	ft_memdel((void **)line);
	return (0);
}
