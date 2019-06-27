/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 11:27:59 by sregnard          #+#    #+#             */
/*   Updated: 2019/01/10 15:03:36 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_file.h"
#include "libft.h"

static char		*get_content(int fd, char *content)
{
	char	*line;
	int		ret;

	content = NULL;
	line = NULL;
	while ((ret = get_next_line(fd, &line) == 1))
	{
		if (!(content = ft_stradd(content, line)))
		{
			ft_memdel((void **)&content);
			ft_memdel((void **)&line);
			return (NULL);
		}
		if (!(content = ft_stradd(content, "\n")))
		{
			ft_memdel((void **)&content);
			ft_memdel((void **)&line);
			return (NULL);
		}
		ft_memdel((void **)&line);
	}
	if (ret == -1)
		ft_memdel((void **)&content);
	return (content);
}

char			**read_file(char *file)
{
	char	**content_tab;
	char	*content;
	int		fd;

	if (ft_strequ(file, "/dev/random") || (fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	if (!(content = get_content(fd, file)))
		return (NULL);
	if (close(fd) == -1)
	{
		ft_memdel((void **)&content);
		return (NULL);
	}
	content_tab = ft_strsplit(content, '\n');
	ft_memdel((void **)&content);
	return (content_tab);
}
