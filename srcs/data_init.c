/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:16:09 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/13 18:12:32 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse.h"

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

static t_cam		*cam_init(t_map ***map)
{
	t_cam		*new;
	t_point		start;

	if (!(new = (t_cam*)malloc(sizeof(t_cam))))
		return (NULL);
	if (!(new->crd_real = (t_point*)malloc(sizeof(t_point))))
		return (NULL);
	if (!(new->crd_map = (t_point*)malloc(sizeof(t_point))))
		return (NULL);
	start = find_start(map);
	new->crd_map->x = start.x;
	new->crd_map->y = start.y;
	new->crd_real->x = new->crd_map->x * SIZE_GRID + SIZE_GRID * 0.5;
	new->crd_real->y = new->crd_map->y * SIZE_GRID + SIZE_GRID * 0.5;
	new->act_inter = pt_set(0, 0);
	new->theta = 310;
	new->h_cam = 0.5;
	new->len_cam = (WIN_WIDTH * new->h_cam) / tan(deg_to_rad(FOV * new->h_cam));
	new->min_theta = FOV / (float)WIN_WIDTH;
	return (new);
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
	data->musics = NULL;
	data->sounds = NULL;
	if (!(data->cam = cam_init(map)))
		ft_exit(&data);
	if (init_window_and_img(data, parse, &size) < 0)
		ft_exit(&data);
	data->ray = init_ray();
	if (sound_init(data) < 0)
		ft_exit(&data);
	return (data);
}
