
#include "main.h"

static t_ptfl		set_coeff_x_y_hori(float deg)
{
	t_ptfl			a;

    if ((deg > 0 && deg < 90) || (deg > 270))
	{
		a.y = (deg > 0 && deg < 90) ? -SIZE_GRID : SIZE_GRID;
		a.x = SIZE_GRID / tanf(deg_to_rad(deg));
		if (a.x < 0)
			a.x = -a.x;
	}
    else
	{
		a.y = (deg > 90 && deg < 180) ? -SIZE_GRID : SIZE_GRID;
		a.x = SIZE_GRID / tanf(deg_to_rad(deg));
		if (a.x > 0)
			a.x = -a.x;
	}
	//printf("deg = %f, a.x = %f, a.y = %f\n", deg ,a.x, a.y);
	return (a);
}

static t_ptfl		set_coeff_x_y_verti(float deg)
{
	t_ptfl			a;

	if (deg > 0 && deg < 180)
	{
		a.x = (deg < 90) ? SIZE_GRID : -SIZE_GRID;
		a.y = (SIZE_GRID * tanf(deg_to_rad(deg)));
		if (a.y > 0)
			a.y = -a.y;
	}
	else
	{
		a.x = (deg > 270) ? SIZE_GRID : -SIZE_GRID;
		a.y = SIZE_GRID * tanf(deg_to_rad(deg));
		if (a.y < 0)
			a.y = -a.y;
	}
	return (a);
}

void				ft_ciel_sol(t_data *data)
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

static void			display_wall(t_data *data)
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
	float		ray_ang;
	float		max_ang;
	t_ptfl		pt_tmp;
	float		ang_inc;
	int			offset;
//	t_ptfl		dist;
	float		coeff;
	t_ptfl		a;
	int			y;
	int			tmp;
	float		nb_inters;
	float		rapport;
	int			i;

	printf("xmax = %d, ymax = %d\n", data->xmax, data->ymax);
	y = data->ray->wall_max;
	i = 0;
//	printf("JE SUIS DANS DISPLAY FLOOR\n");
	ray_ang = rad_to_deg(atan((data->cam->h_cam * (float)WALL_H) / data->ray->dist_w_d));
	max_ang = rad_to_deg(atan((data->cam->h_cam * (float)WIN_HEIGHT) / data->ray->dist_w_d));
	ang_inc = (max_ang - ray_ang) / (float)(WIN_HEIGHT - data->ray->wall_max);
	tmp = WIN_HEIGHT - data->ray->wall_max;
	if (data->ray->dist_h < data->ray->dist_v || data->ray->dist_v < 0)
	{
		pt_tmp = data->ray->hori;
		a = set_coeff_x_y_hori(data->ray->deg);//ray_ang);
		printf("HORI\n");
		offset = (int)pt_tmp.x % (int)data->b_and_w_tiles->size.x;
		nb_inters = data->ray->dist_w_d / a.x;
		coeff = a.y / 64;
		if (coeff < 0)
			coeff = -coeff;
	}
	else
	{
		pt_tmp = data->ray->verti;
		a = set_coeff_x_y_verti(data->ray->deg);//ray_ang);
		offset = (int)pt_tmp.y % (int)data->b_and_w_tiles->size.y;
		nb_inters = data->ray->dist_w_d / a.y;
		coeff = a.x / 64;
		if (coeff < 0)
			coeff = -coeff;
	}
//	coeff = ((float)WIN_HEIGHT - (float)data->ray->wall_max) / (float)WIN_HEIGHT;//(data->ray->dist_w_d / 64) * nb_inters;
	//coeff  = (float)data->b_and_w_tiles->size.y / data->ray->wall_size; // scaling texture
	//coeff = coeff / nb_inters;
	//coeff  = (float)data->b_and_w_tiles->size.y / (((float)WIN_HEIGHT - (float)data->ray->wall_max));//(data->ray->dist_w_d / 64) * nb_inters;
	rapport = nb_inters / tmp;
	printf("deg = %f, a.x = %f, a.y = %f, coeff = %f\n", data->ray->deg ,a.x, a.y, coeff);
	while (y < WIN_HEIGHT)
	{
//		if ((data->ray->deg >= 45 && data->ray->deg < 135) || (data->ray->deg >= 225 && data->ray->deg < 315 ))
//		{
//			offset = abs((int)pt_tmp.y % (int)data->b_and_w_tiles->size.y);
		//	if (data->ray->deg >= 225 && data->ray->deg < 315 )
		//		offset = data->b_and_w_tiles->size.x - 1 - offset;
				pt_to_tex((t_point){data->ray->actual_ray, y}, data->m_img, get_pixel((t_point){(int)offset /* coeff*//*)) % 64*/, (int)((y - data->ray->wall_max /*- 64 * i*/) * (coeff)) % 64/*((pt_tmp.y * coeff)) % 64*/}, data->b_and_w_tiles));
//		}
				//pt_to_tex((t_point){data->ray->actual_ray, y}, data->m_img, get_pixel((t_point){(int)((pt_tmp.x * coeff)) % 64, (int)((y - data->ray->wall_max /*- 64 * i*/) * (coeff)) % 64/*((pt_tmp.y * coeff)) % 64*/}, data->b_and_w_tiles));
//		else
//		{
//			offset = abs((int)pt_tmp.x % (int)data->b_and_w_tiles->size.x);
//			if (data->ray->deg <= 45 || data->ray->deg > 315)
//				offset = abs((int)pt_tmp.y % (int)data->b_and_w_tiles->size.y);
		//		offset = data->b_and_w_tiles->size.y - 1 - offset;
//				pt_to_tex((t_point){data->ray->actual_ray, y}, data->m_img, get_pixel((t_point){(int)((offset * coeff)) % 64, (int)((y - data->ray->wall_max /*- 64 * i*/) * (coeff)) % 64/*((pt_tmp.y * coeff)) % 64*/}, data->b_and_w_tiles));
		
		pt_tmp.y = pt_tmp.y + a.y * rapport;//§coeff.y;
		pt_tmp.x = pt_tmp.x + a.x * rapport;//§coeff.y;
		printf("offset = %d, pt_tmp.x = %f, pt_tmp.y = %f, rapport = %f\n", offset, pt_tmp.x, pt_tmp.y, rapport);
		y++;
//		}
//		i++;
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
