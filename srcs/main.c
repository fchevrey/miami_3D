/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:51:06 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/11 18:07:38 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse.h"
#include "event.h"

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
		{
			ft_putendl_fd("invalid file.", 2);
			return (1);
		}
		map2 = fill_map(parse, &map, parse.nb_elem_line);
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
