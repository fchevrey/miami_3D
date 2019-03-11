
#include "main.h"

static int		set_offset(t_data *data, t_texture *img)
{
	if (data->ray->dist_v < 0 || data->ray->dist_h < data->ray->dist_v)
		data->ray->offset = (int)roundf(data->ray->hori.x) % img->size.x;
	else if (data->ray->dist_h < 0 || data->ray->dist_h > data->ray->dist_v)
		data->ray->offset = (int)roundf(data->ray->verti.y) % img->size.y;
	return (data->ray->offset);
}

static void		sky_ground_rendering(t_data *data)
{
    int				y;

    y = 0;

	if (data->ray->wall_max < WIN_HEIGHT)
	{
		while (y < data->ray->wall_min && y < WIN_HEIGHT)
		{
			pt_to_tex((t_point){data->ray->actual_ray, y}, data->m_img, 0x0087CEEB);
			y++;
		}
		y = data->ray->wall_max;
		while (y < WIN_HEIGHT)
		{
			pt_to_tex((t_point){data->ray->actual_ray, y}, data->m_img, 0x00EED5B7);
			y++;
		}
	}
}

static void		wall_rendering(t_data *data)
{
	t_point			px_to_color;
	float			coeff;
    t_texture		*actual_texture;

	px_to_color = pt_set(data->ray->actual_ray, data->ray->wall_min);
	if ((data->ray->deg >= 0 && data->ray->deg < 180)
	&& data->ray->dist_h < data->ray->dist_v)
		actual_texture = data->wall_texts[0];
	else if ((data->ray->deg >= 180 && data->ray->deg < 360)
	&& data->ray->dist_h < data->ray->dist_v)
		actual_texture = data->wall_texts[1];
	if (((data->ray->deg >= 0 && data->ray->deg < 90)
	|| (data->ray->deg >= 270 && data->ray->deg < 360))
	&& data->ray->dist_v < data->ray->dist_h)
		actual_texture = data->wall_texts[2];
	if ((data->ray->deg >= 90 && data->ray->deg < 270)
	&& data->ray->dist_v < data->ray->dist_h)
		actual_texture = data->wall_texts[3];
	coeff  = (float)actual_texture->size.y / data->ray->wall_size;
	set_offset(data, actual_texture);
	if (data->ray->wall_min < 0)
		px_to_color.y = 0;
    while (px_to_color.y < data->ray->wall_max && px_to_color.y < WIN_HEIGHT)
    {
        pt_to_tex(px_to_color, data->m_img, get_pixel((t_point){data->ray->offset, (int)(coeff * (float)(px_to_color.y - data->ray->wall_min))}, actual_texture));
        px_to_color.y++;
    }
}

static void		column_rendering(t_data *data)
{
    data->ray->wall_min = WIN_HEIGHT / 2 - (int)data->ray->wall_size / 2;
	data->ray->wall_max = data->ray->wall_min + (int)data->ray->wall_size;
	sky_ground_rendering(data);
    wall_rendering(data);
}

void        	rendering(t_data *dt)
{
	float	wall_distance;

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
	draw_mini_map2(dt);
	put_tex_to_ren(dt->m_img, dt->win->ren, (t_point){0, 0}, 0);
	put_tex_to_ren(dt->wall_texts[0], dt->win->ren, (t_point){0, 0}, 0);
	put_tex_to_ren(dt->hud, dt->win->ren, pt_set(0, dt->m_img->size.y), 1);
}
