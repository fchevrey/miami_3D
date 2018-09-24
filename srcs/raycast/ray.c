
#include "main.h"

int         is_in_map(float x, float y, t_data *data)
{
	if (x > (float)data->xmax || x < 0)
		return (0);
	if (y > (float)data->ymax || y < 0)
		return (0);
	return (1);
}

float       return_fish(float deg, float vision)
{
	return (fabsf(deg - vision));
}

void		raycasting(t_data *dt)
{
	float	wall_dist;
	int		tmp;
	int		i;

	i = 0;
	dt->ray->deg = dt->cam->theta + FOV / 2;
	if (dt->ray->deg > 360)
		dt->ray->deg = dt->ray->deg - 360;
	dt->ray->actual_ray = 0;
	while (dt->ray->actual_ray < WIN_WIDTH)
	{
		tmp = dt->obj_ar[i].content;
		dt->ray->dist_w_d = cast_ray(dt);
		wall_dist = dt->ray->dist_w_d * cos(fabs(deg_to_rad(dt->ray->deg
		- dt->cam->theta)));
		dt->ray->wall_size = dt->cam->len_cam * (WALL_H / wall_dist);
		display_column(dt);
		if (dt->ray->deg - dt->cam->min_theta < 0)
			dt->ray->deg = 360 + (dt->ray->deg - dt->cam->min_theta);
		else
			dt->ray->deg -= dt->cam->min_theta;
		if (tmp != dt->obj_ar[i].content)
		{
			dt->obj_ar[i].wall_dist = wall_dist;
			i++;
		}
		dt->ray->actual_ray++;
	}
}

void        display(t_data *dt)
{
	raycasting(dt);
	draw_mini_map2(dt);
//	display_obj(dt);
	put_tex_to_ren(dt->m_img, dt->win->ren, (t_point){0, 0}, 0);
	put_tex_to_ren(dt->obj_texts[0], dt->win->ren, (t_point){0, 300}, 0);
	put_tex_to_ren(dt->wall_texts[1], dt->win->ren, (t_point){0, 0}, 0);
	put_tex_to_ren(dt->wall_texts[2], dt->win->ren, (t_point){64, 0}, 0);
	put_tex_to_ren(dt->wall_texts[3], dt->win->ren, (t_point){128, 0}, 0);
	put_tex_to_ren(dt->hud, dt->win->ren, pt_set(0, dt->m_img->size.y), 1);
}
