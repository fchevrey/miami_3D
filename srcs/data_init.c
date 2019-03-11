/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:16:09 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/11 18:16:58 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse.h"

static void			init_and_load_wall_textures(t_data *data)
{
	int			i;
	t_point		tiles_size;
	char		**titles;
	char		*tex_title;

	i = 0;
	tiles_size = pt_set(64, 64);
	if (!(data->wall_texts = (t_texture**)malloc(sizeof(t_texture*) *
			WALL_TEXTS + 1)))
		malloc_failed("init wall_texts\n");
	data->wall_texts[WALL_TEXTS] = NULL;
	titles = ft_strsplit("lol.tga|space_invader.tga|rainbow.tga|doom.tga", '|');
	while (i < WALL_TEXTS)
	{
		if (!(data->wall_texts[i] = texture_new(tiles_size, data->win->ren)))
		{
			malloc_failed("init one wall_texture\n");
			return ;
		}
		tex_title = ft_strjoin("assets/textures/", titles[i]);
		ft_load_texture(&data->endian, tex_title, data->wall_texts[i]);
		i++;
		ft_strdel(&tex_title);
	}
	ft_tabdel(&titles);
}

static t_ray		*init_ray(void)
{
	t_ray		*new;

	if (!(new = (t_ray*)malloc(sizeof(t_ray))))
		malloc_failed("init ray\n");
	new->deg = 0;
	new->actual_ray = 0;
	new->hori = (t_ptfl){0, 0};
	new->verti = (t_ptfl){0, 0};
	new->dist_h = 0;
	new->dist_v = 0;
	new->offset = 0;
	new->wall_size = 0;
	new->wall_min = 0;
	new->wall_max = 0;
	return (new);
}

static t_cam		*cam_init(t_parse parse)
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
	new->act_inter = pt_set(0, 0);
	new->theta = 180;
	new->h_cam = 0.5;
	new->len_cam = (WIN_WIDTH * new->h_cam) / tan(deg_to_rad(FOV * new->h_cam));
	new->min_theta = FOV / (float)WIN_WIDTH;
	return (new);
}

static int			init_window_and_img(t_data *data, t_parse parse,
		t_point *size)
{
	int i;

	if (!(data->cam = cam_init(parse)))
		return (-1);
	if (!(data->win = win_new(*size, "Wolf 3D")))
		return (-1);
	if (!(data->win->ren = SDL_CreateRenderer(data->win->ptr, -1, 0)))
		return (-1);
	size->y -= HUD_HEIGHT;
	if (!(data->m_img = texture_new(*size, data->win->ren)))
		return (-1);
	init_and_load_wall_textures(data);
	data->musics = NULL;
	data->sounds = NULL;
	data->ray = init_ray();
	size->y = HUD_HEIGHT;
	if (!(data->hud = texture_new(*size, data->win->ren)))
		return (-1);
	i = 0;
	while (i < size->x * size->y)
		data->hud->tab_pxl[i++] = 0xA600A6;
	data->xmax = parse.nb_elem_line;
	data->ymax = parse.nb_line;
	data->walk_channel = -12;
	return (0);
}

t_data				*data_init(t_map ***map, t_parse parse, char **av)
{
	t_data		*data;
	t_point		size;
	t_point		tiles_size;
	char		*chr;

	size = pt_set(WIN_WIDTH, WIN_HEIGHT + HUD_HEIGHT);
	tiles_size = pt_set(64, 64);
	if (!(data = (t_data*)malloc(sizeof(t_data))))
		return (NULL);
	data->map = map;
	data->endian = -1;
	chr = ft_strstr(av[0], "/wolf3d");
	data->path = ft_strsub(av[0], 2, ft_strlen(av[0]) - (ft_strlen(chr) + 1));
	data->map = map;
	if (init_window_and_img(data, parse, &size) < 0)
		ft_exit(&data);
	if (sound_init(data) < 0)
		ft_exit(&data);
	return (data);
}
