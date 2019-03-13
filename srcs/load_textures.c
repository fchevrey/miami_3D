/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:59:39 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/13 13:18:48 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse.h"

static t_texture		**load_loop(t_data *data, char **titles, int max, 
		t_point size)
{
	int				i;
	t_texture		*dst;
	char		*tex_title;

	if (!(dst = (t_texture**)malloc(sizeof(t_texture*) * max + 1)))
		return (NULL);
	data->wall_texts[max] = NULL;
	i = 0;
	while (i < max)
	{
		if (!(dst[i] = texture_new(size, data->win->ren)))
			malloc_failed("texture new\n");
		if (!(tex_title = ft_strjoin("assets/textures/", titles[i])))
			malloc_failed("str join\n");
		if (ft_load_texture(&data->endian, tex_title, data->wall_texts[i])) < 0)
			malloc_failed("load texture\n");
		i++;
		ft_strdel(&tex_title);
	}
	return (dst);
}

static int			init_and_load_wall_textures(t_data *data)
{
	t_point		tiles_size;
	char		**titles;

	if (!(titles = ft_strsplit(
			"lol.tga|space_invader.tga|rainbow.tga|doom.tga", '|')))
		return (-1);
	if (!(data->wall_texts = load_loop(data, titles,
					WALL_TEXTS, pt_set(64, 64))))
		return (-1);
	ft_tabdel(&titles);
	return (0);
}


static int			init_and_load_other_textures(t_data *data)
{
	size_t			i;
	t_point		tiles_size;
	char		**titles;
	char		*tex_title;

	i = 0;
	tiles_size = pt_set(128, 128);
	if (!(data->texts = (t_texture**)malloc(sizeof(t_texture*)
					* 4)))
		malloc_failed("init other textures\n");
	data->texts[3] = NULL;
	if (!(titles = ft_strsplit("shotgun_front.tga|wolf.tga|shotgun_logo.tga", '|')))
		return (-1);
	while (i < 3)
	{
		if (!(data->texts[i] = texture_new(tiles_size, data->win->ren)))
		{
			malloc_failed("init one other textures\n");
			return ;
		}
		if (!(tex_title = ft_strjoin("assets/textures/", titles[i])))
			return;
		ft_load_texture(&data->endian, tex_title, data->texts[i]);
		i++;
		ft_strdel(&tex_title);
	}
	ft_tabdel(&titles);
}

static int	create_hud(t_data *data, t_point *size)
{
	size->y = HUD_HEIGHT;
	if (!(data->hud = texture_new(*size, data->win->ren)))
		return (-1);
	fill_tex_in_color(data->hud, 0xFFFF00FF);
	return (0);
}

int			init_window_and_img(t_data *data, t_parse parse, t_point *size)
{
	if (!(data->win = win_new(*size, "Wolf 3D")))
		return (-1);
	if (!(data->win->ren = SDL_CreateRenderer(data->win->ptr, -1, 0)))
		return (-1);
	SDL_SetRenderDrawBlendMode(data->win->ren, SDL_BLENDMODE_BLEND);
	size->y -= HUD_HEIGHT;
	if (!(data->m_img = texture_new(*size, data->win->ren)))
		return (-1);
	init_and_load_wall_textures(data);//
	init_and_load_other_textures(data);//
	create_hud(data, size);
	data->xmax = parse.nb_elem_line;
	data->ymax = parse.nb_line;
	data->walk_channel = -12;
	return (0);
}
