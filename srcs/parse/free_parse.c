
# include "parse.h"

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