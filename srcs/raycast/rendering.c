/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenetea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:46:05 by cbenetea          #+#    #+#             */
/*   Updated: 2019/03/13 14:46:22 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "raycast.h"

static int			set_offset(t_data *data, t_texture *img)
{
	if (data->ray->dist_v < 0 || data->ray->dist_h < data->ray->dist_v)
		data->ray->offset = (int)roundf(data->ray->hori.x) % img->size.x;
	else if (data->ray->dist_h < 0 || data->ray->dist_h > data->ray->dist_v)
		data->ray->offset = (int)roundf(data->ray->verti.y) % img->size.y;
	return (data->ray->offset);
}

static void			sky_ground_rendering(t_data *data)
{
	int				y;
	int				blue;
	int				beige;

	y = 0;
	blue = 0xFF87CEEB;
	beige = 0xFFEED5B7;
	if (data->ray->wall_max < WIN_HEIGHT)
	{
		while (y < data->ray->wall_min && y < WIN_HEIGHT)
		{
			pt_to_tex(pt_set((int)data->ray->actual_ray, y), data->m_img, blue);
			y++;
		}
		y = data->ray->wall_max;
		while (y < WIN_HEIGHT)
		{
			pt_to_tex(pt_set(
						(int)data->ray->actual_ray, y), data->m_img, beige);
			y++;
		}
	}
}

static void			wall_rendering(t_data *dt, float deg)
{
	t_point			px_to_color;
	float			coeff;
	t_texture		*actual_texture;

	px_to_color = pt_set((int)dt->ray->actual_ray, (int)dt->ray->wall_min);
	if ((deg >= 0 && deg < 180) && dt->ray->dist_h < dt->ray->dist_v)
		actual_texture = dt->wall_texts[0];
	else if ((deg >= 180 && deg < 360) && dt->ray->dist_h < dt->ray->dist_v)
		actual_texture = dt->wall_texts[1];
	else if (((deg >= 0 && deg < 90) || (deg >= 270 && deg < 360))
	&& dt->ray->dist_v < dt->ray->dist_h)
		actual_texture = dt->wall_texts[2];
	else
		actual_texture = dt->wall_texts[3];
	coeff = (float)actual_texture->size.y / dt->ray->wall_size;
	set_offset(dt, actual_texture);
	px_to_color.y = (dt->ray->wall_min < 0) ? 0 : dt->ray->wall_min;
	while (px_to_color.y < dt->ray->wall_max && px_to_color.y < WIN_HEIGHT)
	{
		pt_to_tex(px_to_color, dt->m_img, get_pixel((t_point){dt->ray->offset,
		(int)(coeff * (float)(px_to_color.y - dt->ray->wall_min))},
		actual_texture));
		px_to_color.y++;
	}
}

static void			column_rendering(t_data *data)
{
	data->ray->wall_min = WIN_HEIGHT / 2 - (int)data->ray->wall_size / 2;
	data->ray->wall_max = data->ray->wall_min + (int)data->ray->wall_size;
	sky_ground_rendering(data);
	wall_rendering(data, data->ray->deg);
}

void				rendering(t_data *dt)
{
	float			wall_distance;

	dt->ray->deg = dt->cam->theta + FOV / 2;
	if (dt->ray->deg > 360)
		dt->ray->deg = dt->ray->deg - 360;
	dt->ray->actual_ray = 0;
	while (dt->ray->actual_ray < WIN_WIDTH)
	{
		dt->ray->dist_w_d = return_nearest_wall_dist(dt);
		wall_distance = dt->ray->dist_w_d * cos(fabs(deg_to_rad(dt->ray->deg
		- dt->cam->theta)));
		dt->ray->wall_size = dt->cam->len_cam * (WALL_H / wall_distance);
		column_rendering(dt);
		if (dt->ray->deg - dt->cam->min_theta < 0)
			dt->ray->deg = 360 + (dt->ray->deg - dt->cam->min_theta);
		else
			dt->ray->deg -= dt->cam->min_theta;
		dt->ray->actual_ray++;
	}
	draw_mini_map(dt);
	put_tex_to_ren(dt->m_img, dt->win->ren, pt_set(0, 0), 0);
	render_hud(dt);
}
