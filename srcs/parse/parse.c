
#include "parse.h"

/*int		ft_rank(int nb)
{
	int i;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		i++;
	}
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

int		ft_count_before_space(char *str)
{
	int i;

	i = 0;
	while (*str == ' ')
		str++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (i > 3)
		return (0);
	return (1);
}*/

/*static int		ft_add_list(char *str, t_map **map, int y)
{
	int i;
	int nb;
	int x;

	x = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if (ft_count_before_space(str + i) == 0)
				return (*map ? -1 : -2);
			nb = ft_atoi(str + i);
			if (nb > 255)
				return (*map ? -1 : -2);
			ft_add(x, y, nb, map);
			i += ft_rank(nb) - 1;
			if (str[i] != ' ')
			x++;
		}
		i++;
	}
	return (x);
}*/

static int		ft_only_one_space(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
			return (0);
		i++;
	}
	return (1);
}

static int		ft_only_num(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int		ft_add_list(char *str, t_map **map, int y)
{
	int x;
	char **tab;
	int	nb;

	x = 0;
	if (!ft_only_one_space(str))
		return (*map ? -1 : -2);
	if (!ft_only_num(str))
		return (*map ? -1 : -2);
	tab = ft_strsplit(str, ' ');
	while (tab[x])
	{
		nb = ft_atoi(tab[x]);
		if (nb > 255 || nb < 0)
			return (*map ? -1 : -2);
		ft_add(x, y, nb, map);
		x++;
	}
	return (x);
}

static void		ft_frexit(t_map **map, int fd, char *lin, int err)
{
	if (err != -2)
		free_list(map);
	ft_putstr_fd("invalid file\n", 2);
	free(lin);
	close(fd);
	exit(0);
}

static void		ft_open(char *str, t_map **map, t_parse *parse)
{
	int		fd;
	int		y;
	char	*lin;
	int		x;

	x = 0;
	y = 0;
	parse->nb_elem_line = 0;
	if (((fd = open(str, O_RDONLY))) == -1)
	{
		ft_putstr_fd("can't open files\n", 2);
		exit(1);
	}
	while (get_next_line(fd, &lin) > 0)
	{
		if (!ft_lin_is_good(lin))
			ft_frexit(map, fd, lin, 0);
		x = ft_add_list(lin, map, y);
		if (x < 0)
			ft_frexit(map, fd, lin, x);
		if (parse->nb_elem_line == 0)
			parse->nb_elem_line = x - 1;
		if (x - 1 != parse->nb_elem_line)
			ft_frexit(map, fd, lin, 0);
		free(lin);
		y++;
	}
	free(lin);
	parse->nb_line = y - 1;
	close(fd);
}

int				ft_parse(char *str, t_map **map, t_parse *parse)
{
	ft_open(str, map, parse);
	return (1);
}
