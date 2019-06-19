#include "lem_in.h"

int     add_to_path(t_ant *ant, t_room *room)
{
    t_path	*path;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		return (FAIL);
	path->room = room;
	path->next = NULL;
	if (!ant->path_start)
	{
        ant->path_start = path;
		ant->path = path;
		ant->path_last = path;
		return (SUCCESS);
	}
	path->next = ant->path_start;
    ant->path_start = path;
	return (SUCCESS);
}

void    path_print(t_path *path)
{
    t_path *tmp;

    tmp = path;
    while (tmp)
    {
        ft_putstr(tmp->room->name);
        tmp = tmp->next;
        tmp ? ft_putstr("->") : ft_putstr("\n");
    }
}