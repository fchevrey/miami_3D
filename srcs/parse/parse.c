/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:45:03 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/13 17:52:20 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int		ft_only_one_space(char *str)
{
	int		i;

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
	int		i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '1') && str[i] != ' ')
			return (0);
		i++;
	}
	if (str[0] != '1' || (i <= 0 || str[i - 1] != '1'))
		return (0);
	return (1);
}

static int		ft_add_list(char *str, t_map **map, int y)
{
	int		x;
	char	**tab;
	int		nb;

	x = 0;
	if (!ft_only_one_space(str))
		return (*map ? -1 : -2);
	if (!ft_only_num(str))
		return (*map ? -1 : -2);
	if (!(tab = ft_strsplit(str, ' ')))
		malloc_failed("strsplit");
	while (tab[x])
	{
		nb = ft_atoi(tab[x]);
		if (nb > 255 || nb < 0)
			return (*map ? -1 : -2);
		ft_add(x, y, nb, map);
		x++;
	}
	ft_tabdel(&tab);
	return (x);
}

static void		ft_read(t_map **map, t_parse *parse, int fd)
{
	int		y;
	char	*lin;
	int		x;

	x = 0;
	y = 0;
	parse->nb_elem_line = 0;
	while (get_next_line(fd, &lin) > 0)
	{
		if (!ft_lin_is_good(lin))
			ft_free_exit(map, fd, lin, 0);
		x = ft_add_list(lin, map, y);
		if (x < 0)
			ft_free_exit(map, fd, lin, x);
		if (parse->nb_elem_line == 0)
			parse->nb_elem_line = x - 1;
		if (x - 1 != parse->nb_elem_line)
			ft_free_exit(map, fd, lin, 0);
		free(lin);
		y++;
	}
	free(lin);
	parse->nb_line = y - 1;
	close(fd);
}

int				ft_parse(char *str, t_map **map, t_parse *parse)
{
	int		fd;

	if (((fd = open(str, O_RDONLY))) == -1)
	{
		ft_putstr_fd("can't open files\n", 2);
		exit(1);
	}
	ft_read(map, parse, fd);
	return (1);
}
