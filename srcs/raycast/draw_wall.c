
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

static void		display_floor(t_data *data)
{
 //   (void)data;
	float		ray_ang;
	float		max_ang;
	t_point		pt_tmp;
	float		ang_inc;
	int			offset;
	float		coeff;

	ray_ang = (data->cam->h_cam * (float)WALL_H) / data->ray->dist_w_d;
	max_ang = (data->cam->h_cam * (float)WALL_H) / data->cam->len_cam;
	ang_inc = (max_ang - ray_ang) / (float)(WIN_HEIGHT - data->ray->wall_max);
	coeff  = (float)data->b_and_g_tiles->size.y / (float)(WIN_HEIGHT - data->ray->wall_max);//data->ray->wall_size; // scaling texture
	if (data->ray->dist_h < data->ray->dist_v || data->ray->dist_v < 0)
		pt_tmp = data->ray->hori;
	else
		pt_tmp = data->ray->verti;
	while (ray_ang < max_ang)
	{
	//	pt_tmp.x = pt_tmp.x + coeff.x; // un seul des  deux coeff est a augmenter
		offset = pt_tmp.y % data->b_and_g_tiles->size.y;
        pt_to_tex(pt_tmp, data->m_img, get_pixel((t_point){data->ray->offset, (int)(coeff * (float)(pt_tmp.y - data->ray->wall_max))}, data->b_and_g_tiles));// remplissage de la colonne avec la bonne texture
		ray_ang = ray_ang + ang_inc;
		pt_tmp.y = pt_tmp.y + 1;//§coeff.y;
	}
}

static void		display_ceiling(t_data *data)
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
