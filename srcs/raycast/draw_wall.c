
#include "main.h"

void        ft_ciel_sol(t_data *data)
{
    int y;

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

static void				display_wall(t_data *data)
{
	t_point			px_to_color;
	float			coeff;
    
	px_to_color.x = data->ray->actual_ray;
	px_to_color.y = data->ray->wall_min;
	coeff  = (float)data->b_and_w_tiles->size.y / data->ray->wall_size; // scaling texture
    ft_ciel_sol(data);
    while (px_to_color.y < data->ray->wall_max)
    {
        pt_to_tex(px_to_color, data->m_img, get_pixel((t_point){data->ray->offset, (int)(coeff * (float)(px_to_color.y - data->ray->wall_min))}, data->b_and_g_tiles));
        px_to_color.y++;
    }
}

static void                display_floor(t_data *data)
{
    (void)data;
}

static void                display_ceiling(t_data *data)
{
    (void)data;
}

void            display_column(t_data *data)
{
    data->ray->wall_min = WIN_HEIGHT / 2 - (int)data->ray->wall_size / 2;
	data->ray->wall_max = data->ray->wall_min + (int)data->ray->wall_size;
    display_ceiling(data);
    display_wall(data);
    display_floor(data);
}
