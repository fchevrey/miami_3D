/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:51:06 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/13 18:05:42 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse.h"
#include "event.h"
#include "raycast.h"

static int		lib_initialisation(void)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		return (ft_error("SDL_init error :", SDL_GetError(), NULL));
	if (Mix_Init(MIX_INIT_OGG) == -1)
		return (ft_error("SDL_Mixer  error :", Mix_GetError(), NULL));
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048))
		return (ft_error("SDL_Mixer error :", Mix_GetError(), NULL));
	return (1);
}

static void		destroy_map_and_quit(t_map ***map)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			free(map[i][j]);
			map[i][j] = NULL;
			j++;
		}
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	ft_putendl("invalid file");
	exit(0);
}

static int		check_last_line_of_map(t_map ***map)
{
	int			x;
	int			y;
	t_point		crd;

	y = 0;
	x = 0;
	while (map[y])
		y++;
	y--;
	while (map[y][x])
	{
		if ((map[y][x])->content != 1)
			return (-1);
		x++;
	}
	crd = find_start(map);
	if (crd.x == -1 || crd.y == -1)
		return (-1);
	return (0);
}

int				main(int ac, char **av)
{
	t_parse			parse;
	t_map			*map;
	t_data			*data;
	t_map			***map2;

	map = NULL;
	if (ac > 1 && av[1])
	{
		if (!ft_parse(av[1], &map, &parse) || !map)
			return (ft_error("invalid file.", NULL, NULL));
		if (!(map2 = fill_map(parse, &map, parse.nb_elem_line)))
			return (ft_error("map error", NULL, NULL));
		if (check_last_line_of_map(map2) < 0)
			destroy_map_and_quit(map2);
		if (lib_initialisation() < 0)
			return (0);
		if (!(data = data_init(map2, parse, av)))
			return (0);
		rendering(data);
		game_loop(data);
	}
	else
		ft_putendl("usage : ./wolf3d 'filename'");
	return (0);
}
