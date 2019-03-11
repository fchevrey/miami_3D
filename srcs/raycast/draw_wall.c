
#include "main.h"
void				sky_ground_rendering(t_data *data)
{
    int				y;

    y = 0;
    while (y < data->ray->wall_min)
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

static void			wall_rendering(t_data *data)
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
    while (px_to_color.y < data->ray->wall_max)
    {
        pt_to_tex(px_to_color, data->m_img, get_pixel((t_point){data->ray->offset, (int)(coeff * (float)(px_to_color.y - data->ray->wall_min))}, actual_texture));
        px_to_color.y++;
    }
}

void            column_rendering(t_data *data)
{
    data->ray->wall_min = WIN_HEIGHT / 2 - (int)data->ray->wall_size / 2;
	data->ray->wall_max = data->ray->wall_min + (int)data->ray->wall_size;
	sky_ground_rendering(data);
   // display_ceiling(data);
    wall_rendering(data);
   // display_floor(data);
}
