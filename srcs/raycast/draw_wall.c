
#include "main.h"
void				ft_ciel_sol(t_data *dt, t_ray *act_ray)
{
    int				y;

    y = 0;
    while (y < act_ray->wall_min)
    {
        pt_to_tex((t_point){dt->act_ray, y}, dt->m_img, 0x0087CEEB);
        y++;
    }
	y = act_ray->wall_max;
    while (y < WIN_HEIGHT)
    {
        pt_to_tex((t_point){dt->act_ray, y}, dt->m_img, 0x00DC143C);//0x00EED5B7);
        y++;
    }
}

static t_texture	*wall_text_cardinal_position(t_data *dt)
{
	t_texture		*act_text;

	if ((dt->ray->deg >= 0 && dt->ray->deg < 180)
			&& dt->ray->dist_h < dt->ray->dist_v)
		act_text = dt->wall_texts[0];
	else if ((dt->ray->deg >= 180 && dt->ray->deg < 360)
			&& dt->ray->dist_h < dt->ray->dist_v)
		act_text = dt->wall_texts[1];
	if (((dt->ray->deg >= 0 && dt->ray->deg < 90)
			|| (dt->ray->deg >= 270 && dt->ray->deg < 360))
			&& dt->ray->dist_v < dt->ray->dist_h)
		act_text = dt->wall_texts[2];
	if ((dt->ray->deg >= 90 && dt->ray->deg < 270)
			&& dt->ray->dist_v < dt->ray->dist_h)
		act_text = dt->wall_texts[3];
	return (act_text);
}

static void			display_wall(t_data *dt, t_ray *act_ray)
{
	t_point			px_to_color;
	float			coeff;
	t_texture		*act_text;
	t_color			color;

	px_to_color = pt_set(dt->act_ray, act_ray->wall_min);
	act_text = wall_text_cardinal_position(dt);
	coeff = (float)act_text->size.y / act_ray->wall_size;
	set_offset(act_ray, act_text);
	 while (px_to_color.y < act_ray->wall_max)
	{
		color.c = get_pixel((t_point){dt->ray->offset, (int)(coeff * (float)(px_to_color.y - act_ray->wall_min))}, act_text);
		if (color.argb.a == 0)
			color.c = get_pixel(px_to_color, dt->m_img);
		pt_to_tex(px_to_color, dt->m_img, color.c);
		px_to_color.y++;
	}
}


static void		display_ceiling(t_data *data)
{
    (void)data;
}

void            display_column(t_data *dt, t_ray *act_ray)
{
    act_ray->wall_min = WIN_HEIGHT / 2 - (int)act_ray->wall_size / 2;
	act_ray->wall_max = act_ray->wall_min + (int)act_ray->wall_size;
	ft_ciel_sol(dt, act_ray);
    display_ceiling(dt);
    display_wall(dt, act_ray);
   // display_floor(data);
}

/*
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
*/

/*static void		display_floor(t_data *data)
{
	int			ray;
	t_ptfl		point;
	t_ptfl		scd_point;
	float		scd_point_dist;
	t_ptfl		a;
	t_ptfl		coeff;
	//float		dist;
	float		ray_ang;
	float		max_ang;
	float		ang_inc;

	ray = data->ray->wall_max;
	ray_ang = rad_to_deg(atan((ray - (data->cam->h_cam * (float)WALL_H) / (float)WALL_H)));
	max_ang = rad_to_deg(atan((data->cam->h_cam * (float)WIN_HEIGHT) / data->ray->dist_w_d));
	ang_inc = (max_ang - ray_ang) / (float)ray;
	scd_point_dist = data->cam->h_cam / (sinf(deg_to_rad(ray_ang + ang_inc)));
	if (data->ray->dist_h < data->ray->dist_v || data->ray->dist_v < 0)
	{
		point = data->ray->hori;
		coeff = set_coeff_x_y_hori(data->ray->deg);//ray_ang);
		//dist = dist_h;//fabs(point.y - (float)data->cam->crd_real.y);
	}
	else
	{
		point = data->ray->verti;
		coeff = set_coeff_x_y_verti(data->ray->deg);//ray_ang);
		//dist = dist_v;//fabs(point.x - (float)data->cam->crd_real.x);
	}
	coeff.x = coeff.x / 64;
	coeff.y = coeff.y / 64;
//	scd_point_dist /

//	scd_point_dist = (tanf(deg_to_rad(ray_ang + ang_inc))) * data->cam->h_cam;
	scd_point.x = data->cam->crd_real->x + (point.x - data->cam->crd_real->x) * (((data->cam->h_cam * WALL_H) * tanf(deg_to_rad(max_ang))) / (data->ray->dist_w_d * cos(fabs(deg_to_rad(data->ray->deg - data->cam->theta)))));
	scd_point.y = data->cam->crd_real->y + (point.y - data->cam->crd_real->y) * (((data->cam->h_cam * WALL_H) * tanf(deg_to_rad(max_ang))) / (data->ray->dist_w_d * cos(fabs(deg_to_rad(data->ray->deg - data->cam->theta)))));
		printf("ray = %d, scd_point.x = %f, scd_point.y = %f\n", ray, scd_point.x, scd_point.y);
	a.x = scd_point.x - point.x;
	a.y = scd_point.y - point.y;
	printf("a.x = %f, a.y = %f\n", a.x, a.y);
	while (ray < WIN_HEIGHT)
	{
		pt_to_tex((t_point){data->ray->actual_ray, ray}, data->m_img, get_pixel((t_point){(int)(point.x * 64) % 64, (int)(point.y * 64) % 64}, data->floor_texts[0]));
		point.x = point.x + a.x;
		point.y = point.y + a.y;
		printf("point.x = %f, point.y = %f\n", point.x, point.y);
		ray_ang = ray_ang + ang_inc;
		ray++;
	}
}*/
/*
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
//	coeff  = (float)data->b_and_w_tiles->size.y / data->ray->wall_size; // scaling texture
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
//	printf("deg = %f, a.x = %f, a.y = %f, coeff = %f\n", data->ray->deg ,a.x, a.y, coeff);
	while (y < WIN_HEIGHT)
	{
//		if ((data->ray->deg >= 45 && data->ray->deg < 135) || (data->ray->deg >= 225 && data->ray->deg < 315 ))
//		{
//			offset = abs((int)pt_tmp.y % (int)data->b_and_w_tiles->size.y);
		//	if (data->ray->deg >= 225 && data->ray->deg < 315 )
		//		offset = data->b_and_w_tiles->size.x - 1 - offset;
//OK				pt_to_tex((t_point){data->ray->actual_ray, y}, data->m_img, get_pixel((t_point){(int)offset  coeff)) % 64, (int)((y - data->ray->wall_max - 64 * i) * (coeff)) % 64((pt_tmp.y * coeff)) % 64}, data->b_and_w_tiles));
//		}
				pt_to_tex((t_point){data->ray->actual_ray, y}, data->m_img, get_pixel((t_point){(int)((pt_tmp.x * coeff)) % 64, (int)((y - data->ray->wall_max - 64 * i) * (coeff)) % 64((pt_tmp.y * coeff)) % 64}, data->b_and_w_tiles));
				//pt_to_tex((t_point){data->ray->actual_ray, y}, data->m_img, get_pixel((t_point){(int)((pt_tmp.x * coeff)) % 64, (int)((y - data->ray->wall_max - 64 * i) * (coeff)) % 64((pt_tmp.y * coeff)) % 64}, data->b_and_w_tiles));
//		else
//		{
//			offset = abs((int)pt_tmp.x % (int)data->b_and_w_tiles->size.x);
//			if (data->ray->deg <= 45 || data->ray->deg > 315)
//				offset = abs((int)pt_tmp.y % (int)data->b_and_w_tiles->size.y);
		//		offset = data->b_and_w_tiles->size.y - 1 - offset;
//				pt_to_tex((t_point){data->ray->actual_ray, y}, data->m_img, get_pixel((t_point){(int)((offset * coeff)) % 64, (int)((y - data->ray->wall_max - 64 * i) * (coeff)) % 64((pt_tmp.y * coeff)) % 64}, data->b_and_w_tiles));
		
		pt_tmp.y = pt_tmp.y + a.y * rapport;//§coeff.y;
		pt_tmp.x = pt_tmp.x + a.x * rapport;//§coeff.y;
//		printf("offset = %d, pt_tmp.x = %f, pt_tmp.y = %f, rapport = %f\n", offset, pt_tmp.x, pt_tmp.y, rapport);
		y++;
//		}
//		i++;
	}
}*/
