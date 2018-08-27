
#include "parse.h"

void			ft_add(int x, int y, int content, t_map **map)
{
	t_map *new;

	if (!(new = (t_map *)malloc(sizeof(t_map))))
		malloc_failed("ft_add");
	new->next = NULL;
	new->x = x;
	new->y = y;
    new->content = content;
	if (!*map)
	{
		new->prev = NULL;
		*map = new;
	}
	else
	{
		while ((*map)->next)
			*map = (*map)->next;
		(*map)->next = new;
		(*map)->next->prev = *map;
		(*map)->next->next = NULL;
	}
}

/*
** double array de pointeur sur structure
** j'utilise ma liste chainee pour en
** faire un tableau
*/

t_map			***ft_fill_tab(t_parse parse, t_map **map)
{
	t_map		***new;
	t_map		*tmp;
	int			y;
	int			x;

	y = 0;
	tmp = *map;
	if (!(new = (t_map ***)malloc(sizeof(t_map **) * (parse.nb_line + 2))))
		malloc_failed("ft_fill_tab");
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		x = 0;
		if (!(new[y] = (t_map **)malloc(sizeof(t_map *) * (parse.nb_elem_line + 2))))
			malloc_failed("ft_fill_tab2");
		while (x <= parse.nb_elem_line)
		{
			new[y][x] = tmp;
			x++;
			tmp = tmp->next;
		}
		new[y][x] = NULL;
		y++;
	}
	new[y] = NULL;
	return (new);
}

int				ft_lin_is_good(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && (str[i] != ' ')
		&& (str[i + 1] && str[i] != '-' && ((str[i] < '0' || str[i] > '9'))))
			return (0);
		if (str[i] == ' ' && str[i + 1] == ' ')
			return (0);
		if (str[i] == ' ' && str[i + 1] == '\0')
			return (0);
		i++;
	}
	return (1);
}

void			malloc_failed(char *str)
{
    ft_putstr(str);
	ft_putendl(" : has failed");
	exit(EXIT_FAILURE);
}
