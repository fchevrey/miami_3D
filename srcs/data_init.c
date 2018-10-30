#include "main.h"

void			init_obj_array(t_data *dt)
{
	int			i;
	int			j;

	i = 0;
	dt->last_obj = pt_set(-1, -1);
	while (i < OBJ_NB)
	{
		j = 0;
		dt->obj_ar[i].content = -1;
		dt->obj_ar[i].index = i;
		dt->obj_ar[i].x = -1;
		dt->obj_ar[i].width = -1;
		while (j < WIN_WIDTH)
		{
			dt->obj_ar[i].coord[j].ray_nb = -1;
			dt->obj_ar[i].coord[j].pt = ptfl_set(-1.0, -1.0);
			dt->obj_ar[i].coord[j].pt_map = pt_set(-1, -1);
			dt->obj_ar[i].coord[j].obj_dist = -1;
			dt->obj_ar[i].coord[j].obj_height = -1;
			dt->obj_ar[i].coord[j].obj_depth = -1;
			dt->obj_ar[i].coord[j].wall_dist = -1;
			j++;
		}
		i++;
	}
}

void			init_and_load_obj_textures(t_data *dt)
{
	int			i;
	t_point		text_size;

	i = 0;
	text_size = pt_set(64, 64);
	if (!(dt->obj_texts = (t_texture**)malloc(sizeof(t_texture*) * OBJ_TEXTS + 1)))
		malloc_failed("init obj_texts\n");
	dt->obj_texts[OBJ_TEXTS] = NULL;
	while (i < OBJ_TEXTS)
	{
		if (!(dt->obj_texts[i] = texture_new(text_size, dt->win->ren)))
		{
			malloc_failed("init obj_texture\n");
			return ;
		}
		if (i == 0)
			ft_load_texture(&dt->endian, "assets/textures/candle.tga", dt->obj_texts[i]);
		else
			ft_load_texture(&dt->endian, "assets/textures/candle.tga", dt->obj_texts[i]);
		i++;
	}
}

void			init_and_load_wall_textures(t_data *dt)
{
	int			i;
	t_point		tiles_size;

	i = 0;
	tiles_size = pt_set(64, 64);
	if (!(dt->wall_texts = (t_texture**)malloc(sizeof(t_texture*) * WALL_TEXTS + 1)))
		malloc_failed("init wall_texts\n");
	dt->wall_texts[WALL_TEXTS] = NULL;
	while (i < WALL_TEXTS)
	{
		if (!(dt->wall_texts[i] = texture_new(tiles_size, dt->win->ren)))
		{
			malloc_failed("init one wall_texture\n");
			return ;
		}
		if (i == 0)
			ft_load_texture(&dt->endian, "assets/textures/doom.tga", dt->wall_texts[i]);
		else if (i == 1)
			ft_load_texture(&dt->endian, "assets/textures/lol.tga", dt->wall_texts[i]);
		else if (i == 2)
			ft_load_texture(&dt->endian, "assets/textures/rainbow.tga", dt->wall_texts[i]);
		else if (i == 3)
			ft_load_texture(&dt->endian, "assets/textures/space_invader.tga", dt->wall_texts[i]);
		i++;
	}
}

void			init_and_load_floor_textures(t_data *data)
{
	int			i;
	t_point		tiles_size;

	i = 0;
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
		ft_load_texture(&data->endian, "assets/textures/2.tga", data->floor_texts[i]);
		i++;
	}
}

void			init_ray_ar(t_data *dt)
{
	int			i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		if (!(dt->ray_ar[i] = (t_ray*)malloc(sizeof(t_ray))))
			malloc_failed("init ray\n"); //malloc error
		dt->ray_ar[i]->deg = 0.0;
		dt->ray_ar[i]->act_ray = 0;
		dt->ray_ar[i]->coeff_h = ptfl_set(-1.0, -1.0);
		dt->ray_ar[i]->coeff_v = ptfl_set(-1.0, -1.0);
		dt->ray_ar[i]->hori = (t_ptfl){0.0, 0.0};
		dt->ray_ar[i]->verti = (t_ptfl){0.0, 0.0};
		dt->ray_ar[i]->dist_h = 0.0;
		dt->ray_ar[i]->dist_v = 0.0;
		dt->ray_ar[i]->dist_w_d = 0.0;
		dt->ray_ar[i]->wall_dist = 0.0;
		dt->ray_ar[i]->offset = 0;
		dt->ray_ar[i]->wall_size = 0.0;
		dt->ray_ar[i]->wall_min = 0;
		dt->ray_ar[i]->wall_max = 0;
		i++;
	}
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
	char		*chr;

	size = pt_set(WIN_WIDTH, WIN_HEIGHT + HUD_HEIGHT);
	if (!(data = (t_data*)malloc(sizeof(t_data))))
		return (NULL);
	data->map = map;
	data->endian = -1;
	printf("DATA->ENDIAN = %d\n", data->endian);
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
	init_obj_array(data);
	init_and_load_obj_textures(data);
	init_ray_ar(data);
	data->musics = NULL;
	data->sounds = NULL;
	data->musics = NULL;
	data->map = map;
	size.y = HUD_HEIGHT;
	if (!(data->hud = texture_new(size, data->win->ren)))
		return (NULL);
	for (int i = 0; i < size.x * size.y; i++)
		data->hud->tab_pxl[i] = 0xA600A6;
	data->xmax = parse.nb_elem_line;
	data->ymax = parse.nb_line;
	data->act_ray = 0;
	data->walk_channel = -12;
	if (sound_init(data) < 0)
		ft_exit(&data);
	ft_putstr("FIN DE DATA INIT\n");
	return (data);
}
