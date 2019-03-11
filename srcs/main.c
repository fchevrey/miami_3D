
#include "main.h"
#include "parse.h"
#include "event.h"
#include "assets.h"

void	check_theta(int i, int j, int x, int y, t_data *data)
{
	if (j == x + 1 && i == y && (data->cam->theta > 315 || data->cam->theta < 45))
		ft_putstr("\033[33;43m");//vert
	else if (j == x  && i == y + 1 && (data->cam->theta <= 315 && data->cam->theta > 225))
		ft_putstr("\033[33;43m");//jaune
	else if (j == x-1  && i == y && (data->cam->theta <= 225 && data->cam->theta > 135))
		ft_putstr("\033[33;43m");//bleu
	else if (j == x  && i == y - 1 && (data->cam->theta <= 135 && data->cam->theta > 45))
		ft_putstr("\033[33;43m");//noir
}

void	display_map(t_map ***map2, int x, int y, t_data *data)
{
	int		i,j;
	i = 0;
	while (map2[i])
	{
		j = 0;
		while (map2[i][j])
		{
			if (i == y && j == x)
				ft_putstr("\033[35;45m"); //player
			else if (map2[i][j]->content == 1)
				ft_putstr("\033[31;41m"); //wall
			else if (map2[i][j]->content == 0)
				ft_putstr("\033[37;47m"); //nothing
			check_theta(i, j, x, y, data);
			ft_putnbr(map2[i][j]->content);
			ft_putstr("\033[0m");
			j++;
		}
		ft_putchar('\n');
		i++;
	}
	ft_putchar('\n');
}

static int		lib_initialisation(void)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		return (ft_error("SDL_init error :", SDL_GetError(), NULL));
	if ( Mix_Init(MIX_INIT_OGG) == -1)
		return (ft_error("SDL_Mixer  error :", Mix_GetError(), NULL));
	printf("%s\n", Mix_GetError());
	//if ( Mix_OpenAudio( 44100, AUDIO_S16SYS, 1, 2048) == -1)
	if ( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 ))
		return (ft_error("SDL_Mixer  error :", Mix_GetError(), NULL));
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
			ft_putendl_fd("Le fichier est pas bon", 2);
			return (1);
		}
		map2 = ft_fill_tab(parse, &map);
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
