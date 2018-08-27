#include "main.h"

t_cam		*cam_init(t_parse parse)
{
	t_cam *new;

	if (!(new = (t_cam*)malloc(sizeof(t_cam))))
		return (NULL);
	if (!(new->crd_real = (t_point*)malloc(sizeof(t_point))))
		return (NULL);
	if (!(new->crd_map = (t_point*)malloc(sizeof(t_point))))
		return (NULL);
	new->crd_map->x = parse.nb_elem_line * 0.5;
	new->crd_map->y = parse.nb_line * 0.5;
	new->crd_real->x = new->crd_map->x * SIZE_GRID + SIZE_GRID * 0.5;
	new->crd_real->y = new->crd_map->y * SIZE_GRID + SIZE_GRID * 0.5;
	printf("real x : %d | real y : %d\n",new->crd_real->x, new->crd_real->y);
	new->theta = 90;
	new->len_cam = (WIN_WIDTH * 0.5) / tan(deg_to_rad(FOV * 0.5));
	new->h_cam = WALL_H * 0.5;
	new->min_theta = FOV / (float)WIN_WIDTH;
	return (new);
}

t_data		*data_init(t_map ***map, t_parse parse, char **av)
{
	t_data		*data;
	t_point		size;
	t_point		tiles_size;
	char		*chr;

	size = pt_set(WIN_WIDTH, WIN_HEIGHT);
	tiles_size = pt_set(256, 256);
	if (!(data = (t_data*)malloc(sizeof(t_data))))
		return (NULL);
	data->map = map;
	chr = ft_strstr(av[0], "/wolf3d");
	printf("\n  == chr = %s\n  ==", chr);
	data->path = ft_strsub(av[0], 2, ft_strlen(av[0]) - (ft_strlen(chr) + 1));
	if (!(data->cam = cam_init(parse)))
		return (NULL);
	if (!(data->win = win_new(size, "Wolf 3D")))
		return (NULL);
	if (!(data->win->ren = SDL_CreateRenderer(data->win->ptr, -1, 0)))
		return (NULL);
	if (!(data->m_img = texture_new(size, data->win->ren)))
		return (NULL);
	if (!(data->b_and_w_tiles = texture_new(tiles_size, data->win->ren)))
		return (NULL);
	data->sounds = NULL;
	data->musics = NULL;
	data->map = map;
	data->xmax = parse.nb_elem_line;
	data->ymax = parse.nb_line;
	data->walk_channel = -12;
	if (sound_init(data) < 0)
		ft_exit(&data);
	return (data);
}
