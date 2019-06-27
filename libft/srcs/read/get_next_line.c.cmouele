/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:31:59 by cmouele           #+#    #+#             */
/*   Updated: 2018/12/05 12:59:04 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_fill_buff() fills static_buff with its value if it exists, concatenated
** with the string returned from read() in ft_read().
*/

static int	ft_fill_buff(char **static_buff, char *buff)
{
	char	*static_buff_cpy;

	if (*static_buff == NULL)
	{
		*static_buff = ft_strdup(buff);
		if (*static_buff == NULL)
			return (-1);
	}
	else
	{
		static_buff_cpy = ft_strdup(*static_buff);
		if (static_buff_cpy == NULL)
			return (-1);
		ft_strdel(static_buff);
		*static_buff = ft_strjoin(static_buff_cpy, buff);
		if (*static_buff == NULL)
			return (-1);
		ft_strdel(&static_buff_cpy);
	}
	return (0);
}

/*
** ft_read() reads the file and returns -1 in case of problem, 1 if the file
** was entirely browsed and a line was found, 0 if the file was entirely
** browsed and no line was found. Else, it calls ft_fill_buff() to fill
** static_buff and get_next_line() to retrieve a line.
*/

static int	ft_read(const int fd, char **static_buff, char **line)
{
	int		read_nb;
	char	buff[BUFF_SIZE + 1];

	read_nb = read(fd, buff, BUFF_SIZE);
	if (read_nb == -1)
		return (-1);
	if (read_nb == 0)
	{
		if (*line)
			return (1);
		else
			return (0);
	}
	buff[read_nb] = '\0';
	if (ft_fill_buff(static_buff, buff) == -1)
		return (-1);
	return (get_next_line(fd, line));
}

/*
** If \n exists in the string, we fill line with what is before \n, and fill
** static_buff with what is after \n.
*/

static int	ft_n_found(char **static_buff, char **line, int c)
{
	char	*tmp_str;

	tmp_str = ft_strdup(*static_buff + c + 1);
	*line = ft_strsub(*static_buff, 0, c);
	if (tmp_str == NULL || *line == NULL)
		return (-1);
	ft_strdel(static_buff);
	*static_buff = tmp_str;
	return (1);
}

/*
** If \n isn't found, we call ft_read() to get another piece of the file. But if
** we are at the end of the file, we check the existence of line to return 1 or
** 0.
*/

static int	ft_n_notfound(const int fd, char **static_buff, char **line, int c)
{
	int result;

	result = ft_read(fd, static_buff, line);
	if (result == 0)
	{
		*line = ft_strsub(*static_buff, 0, c);
		if (*line == NULL)
			return (-1);
		ft_strdel(static_buff);
		return (ft_strlen(*line) > 0);
	}
	return (result);
}

/*
** get_next_line() checks if static_buff (what we got after \n) is empty or
** not. If empty, we call ft_read() to fill it. Else, we check the presence of
** \n. If \n exists, we call ft_n_found(). If \n is not found, we call
** ft_n_notfound().
*/

int			get_next_line(const int fd, char **line)
{
	static char	*static_buff = NULL;
	int			c;

	if (fd < 0 || fd > FD_MAX || line == NULL || BUFF_SIZE < 0)
		return (-1);
	*line = NULL;
	if (static_buff)
	{
		c = 0;
		while (static_buff[c] && static_buff[c] != '\n')
			c++;
		if (static_buff[c] == '\0')
			return (ft_n_notfound(fd, &static_buff, line, c));
		if (static_buff[c] == '\n')
			return (ft_n_found(&static_buff, line, c));
	}
	return (ft_read(fd, &static_buff, line));
}
