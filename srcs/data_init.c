#include "main.h"

void			init_and_load_wall_textures(t_data *data)
{
	int			i;
	t_point		tiles_size;

	printf("DEBUT DE INIT WALL\n");
	i = 0;
	tiles_size = pt_set(64, 64);
	if (!(data->wall_texts = (t_texture**)malloc(sizeof(t_texture*) * WALL_TEXTS + 1)))
		malloc_failed("init wall_texts\n"); //malloc error
	data->wall_texts[WALL_TEXTS] = NULL;
	while (i < WALL_TEXTS)
	{
		if (!(data->wall_texts[i] = texture_new(tiles_size, data->win->ren)))
		{
			malloc_failed("init one wall_texture\n"); //malloc error
			return ;
		}
		if (i == 0)
			ft_load_texture("assets/textures/doom.tga", data->wall_texts[i]);
		else if (i == 1)
			ft_load_texture("assets/textures/lol.tga", data->wall_texts[i]);
		else if (i == 2)
			ft_load_texture("assets/textures/rainbow.tga", data->wall_texts[i]);
		else if (i == 3)
			ft_load_texture("assets/textures/space_invader.tga", data->wall_texts[i]);
		i++;
	}
	printf("FIN DE INIT WALL\n");
}
void			init_and_load_floor_textures(t_data *data)
{
	int			i;
	t_point		tiles_size;

	i = 0;
	printf("DEBUT DE INIT FLOOR\n");
	tiles_size = pt_set(64, 64);
	if (!(data->floor_texts = (t_texture**)malloc(sizeof(t_texture*) * FLOOR_TEXTS + 1)))
		malloc_failed("init floor_texts\n"); //malloc error
	data->floor_texts[FLOOR_TEXTS] = NULL;
	while (i < FLOOR_TEXTS)
	{
		if (!(data->floor_texts[i] = texture_new(tiles_size, data->win->ren)))
		{
			malloc_failed("init one floor_texture\n"); //malloc error
			return ;
		}
		ft_load_texture("assets/textures/2.tga", data->floor_texts[i]);
		i++;
	}
	printf("FIN DE INIT FLOOR\n");
}

t_ray			*init_ray()

{
	t_ray		*new;
	if (!(new = (t_ray*)malloc(sizeof(t_ray))))
		malloc_failed("init ray\n"); //malloc error
	new->deg = 0;
	new->actual_ray = 0;
	new->hori = (t_ptfl){0,0};
	new->verti = (t_ptfl){0,0};
	new->dist_h = 0;
	new->dist_v = 0;
	new->offset = 0;
	new->wall_size = 0;
	new->wall_min = 0;
	new->wall_max = 0;
	return (new);
}

t_cam			*cam_init(t_parse parse)
{
	t_cam		*new;

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
	new->act_inter = pt_set(0, 0);
	new->theta = 180;
	new->h_cam = 0.5;
	new->len_cam = (WIN_WIDTH * new->h_cam) / tan(deg_to_rad(FOV * new->h_cam));
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
	tiles_size = pt_set(64, 64);
	if (!(data = (t_data*)malloc(sizeof(t_data))))
		return (NULL);
	data->map = map;
	chr = ft_strstr(av[0], "/wolf3d");
	//printf("\n  == chr = %s\n  ==", chr);
	data->path = ft_strsub(av[0], 2, ft_strlen(av[0]) - (ft_strlen(chr) + 1));
	if (!(data->cam = cam_init(parse)))
		return (NULL);
	if (!(data->win = win_new(size, "Wolf 3D")))
		return (NULL);
	if (!(data->win->ren = SDL_CreateRenderer(data->win->ptr, -1, 0)))
		return (NULL);
	size.y -= HUD_HEIGHT;
	if (!(data->m_img = texture_new(size, data->win->ren)))
		return (NULL);
	init_and_load_floor_textures(data);
	init_and_load_wall_textures(data);
	data->musics = NULL;
	data->sounds = NULL;
	data->musics = NULL;
	data->map = map;
	data->ray = init_ray();
	size.y = HUD_HEIGHT;
	if (!(data->hud = texture_new(size, data->win->ren)))
		return (NULL);
	for (int i = 0; i < size.x * size.y; i++)
		data->hud->tab_pxl[i] = 0xA600A6;
	data->xmax = parse.nb_elem_line;
	data->ymax = parse.nb_line;
	data->walk_channel = -12;
	if (sound_init(data) < 0)
		ft_exit(&data);
	return (data);
}
