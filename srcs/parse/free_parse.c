
#include "parse.h"

void		free_list(t_map **list)
{
	t_map *tmp;

	while ((*list) && (*list)->prev)
		(*list) = (*list)->prev;
	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}

void		freetab(t_map ***list)
{
	int i;
	int j;

	i = 0;
	while (list[i])
	{
		j = 0;
		while (list[i][j])
		{
			free(list[i][j]);
			j++;
		}
		free(list[i]);
		i++;
	}
	free(list);
}

void		ft_free_exit(t_map **map, int fd, char *lin, int err)
{
	if (err != -2)
		free_list(map);
	ft_putstr_fd("invalid file\n", 2);
	free(lin);
	close(fd);
	exit(0);
}
