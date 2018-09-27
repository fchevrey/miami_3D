
#include "main.h"

int         is_in_map(float x, float y, t_data *dt)
{
	if (x > (float)dt->xmax || x < 0)
		return (0);
	if (y > (float)dt->ymax || y < 0)
		return (0);
	return (1);
}

float			return_fish(float deg, float vision)
{
	return (fabsf(deg - vision));
}

static void		set_act_ray_wall_values(t_data *dt, t_ray *act_ray)
{
	act_ray->wall_dist = act_ray->dist_w_d
		* cos(fabs(deg_to_rad(act_ray->deg - dt->cam->theta)));
	act_ray->wall_size = dt->cam->len_cam
		* (WALL_H / act_ray->wall_dist);
}

void			raycasting(t_data *dt)
{
//	float		wall_dist;
	int			tmp;
	int			i;

	ft_putstr("RAYCASTING\n");
	i = 0;
	dt->act_ray = 0;
	dt->ray_ar[dt->act_ray]->deg = dt->cam->theta + FOV / 2;
	ft_putstr("RAYCASTING 1\n");
	if (dt->ray_ar[dt->act_ray]->deg > 360)
		dt->ray_ar[dt->act_ray]->deg = dt->ray_ar[dt->act_ray]->deg - 360;
	ft_putstr("RAYCASTING 2\n");
	dt->ray_ar[dt->act_ray]->act_ray = 0;
	ft_putstr("RAYCASTING 3\n");
	while (dt->act_ray < WIN_WIDTH)
	{
		tmp = dt->obj_ar[i].content;
	ft_putstr("RAYCASTING 4\n");
		cast_ray(dt, dt->ray_ar[dt->act_ray]);
	ft_putstr("RAYCASTING 5\n");
		set_act_ray_wall_values(dt, dt->ray_ar[dt->act_ray]);
	ft_putstr("RAYCASTING 6\n");
//		dt->ray_ar[dt->act_ray]->wall_dist = dt->ray_ar[dt->act_ray]->dist_w_d
//			* cos(fabs(deg_to_rad(dt->ray_ar[dt->act_ray]->deg - dt->cam->theta)));
//		dt->ray_ar[dt->act_ray]->wall_size = dt->cam->len_cam
//			* (WALL_H / dt->ray_ar[dt->act_ray]->wall_dist);
		display_column(dt, dt->ray_ar[dt->act_ray]);
	ft_putstr("RAYCASTING 7\n");
		if (tmp != dt->obj_ar[i].content)
		{
			dt->obj_ar[i].wall_dist = dt->ray_ar[dt->act_ray]->wall_dist;
			i++;
		}
		if ((dt->act_ray + 1) < WIN_WIDTH && dt->ray_ar[dt->act_ray]->deg - dt->cam->min_theta < 0)
			dt->ray_ar[dt->act_ray + 1]->deg = 360 + (dt->ray_ar[dt->act_ray]->deg - dt->cam->min_theta);
		else if ((dt->act_ray + 1) < WIN_WIDTH)
			dt->ray_ar[dt->act_ray + 1]->deg -= dt->cam->min_theta;
		dt->act_ray++;
	}
	ft_putstr("RAYCASTING FIN\n");
}

void        display(t_data *dt)
{
	raycasting(dt);
	draw_mini_map2(dt);
//	display_obj(dt);
	put_tex_to_ren(dt->m_img, dt->win->ren, (t_point){0, 0}, 0);
//	put_tex_to_ren(dt->obj_texts[0], dt->win->ren, (t_point){300, 300}, 0);
	put_tex_to_ren(dt->wall_texts[1], dt->win->ren, (t_point){0, 0}, 0);
	put_tex_to_ren(dt->wall_texts[2], dt->win->ren, (t_point){64, 0}, 0);
	put_tex_to_ren(dt->wall_texts[3], dt->win->ren, (t_point){128, 0}, 0);
	put_tex_to_ren(dt->hud, dt->win->ren, pt_set(0, dt->m_img->size.y), 1);
}
