
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
	ft_putstr("actual ray wall size :");
	ft_putnbr(act_ray->wall_size); ft_putstr(" ; ");
	ft_putstr("actual ray wall dist :");
	ft_putnbr(act_ray->wall_dist);
	ft_putstr("\n");
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
	if (dt->ray_ar[dt->act_ray]->deg > 360)
		dt->ray_ar[dt->act_ray]->deg = dt->ray_ar[dt->act_ray]->deg - 360;
	dt->ray_ar[dt->act_ray]->act_ray = 0;
	while (dt->act_ray < WIN_WIDTH)
	{
		tmp = dt->obj_ar[i].content;
		cast_ray(dt, dt->ray_ar[dt->act_ray]);
		set_act_ray_wall_values(dt, dt->ray_ar[dt->act_ray]);
	ft_putstr("actual ray number :");
	ft_putnbr(dt->act_ray); ft_putstr("\n");
		dt->ray_ar[dt->act_ray]->wall_dist = dt->ray_ar[dt->act_ray]->dist_w_d
			* cos(fabs(deg_to_rad(dt->ray_ar[dt->act_ray]->deg - dt->cam->theta)));
		dt->ray_ar[dt->act_ray]->wall_size = dt->cam->len_cam
			* (WALL_H / dt->ray_ar[dt->act_ray]->wall_dist);
		display_column(dt, dt->ray_ar[dt->act_ray]);
		if (tmp != dt->obj_ar[i].content)
		{
			dt->obj_ar[i].wall_dist = dt->ray_ar[dt->act_ray]->wall_dist;
			i++;
		}
		if (((dt->act_ray + 1) < WIN_WIDTH) && ((dt->ray_ar[dt->act_ray]->deg - dt->cam->min_theta) < 0))
		{
			dt->ray_ar[dt->act_ray + 1]->deg = 360 + (dt->ray_ar[dt->act_ray]->deg - dt->cam->min_theta);
			ft_putstr("Deg < 0\n");
		}
		else if ((dt->act_ray + 1) < WIN_WIDTH)
		{
			dt->ray_ar[dt->act_ray + 1]->deg = (dt->ray_ar[dt->act_ray]->deg - dt->cam->min_theta);
			ft_putstr("Deg > 0\n");
		}
		printf("dist_H = %f; dist_V = %f; deg = %f ; WIN_WIDTH = %d; min_theta = %f\n", dt->ray_ar[dt->act_ray]->dist_h, dt->ray_ar[dt->act_ray]->dist_v, dt->ray_ar[dt->act_ray]->deg, WIN_WIDTH, dt->cam->min_theta);
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
	put_tex_to_ren(dt->wall_texts[0], dt->win->ren, (t_point){192, 0}, 0);
	put_tex_to_ren(dt->wall_texts[1], dt->win->ren, (t_point){0, 0}, 0);
	put_tex_to_ren(dt->wall_texts[2], dt->win->ren, (t_point){64, 0}, 0);
	put_tex_to_ren(dt->wall_texts[3], dt->win->ren, (t_point){128, 0}, 0);
	put_tex_to_ren(dt->hud, dt->win->ren, pt_set(0, WIN_HEIGHT), 1);
}
